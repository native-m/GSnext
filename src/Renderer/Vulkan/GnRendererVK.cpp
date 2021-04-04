#include "GnRendererVK.h"
#include "GnDeviceVK.h"

#include <gsnext/GnLog.h>

static const char* g_enabledDeviceLayers[] = {
    "VK_LAYER_KHRONOS_validation",
    "VK_LAYER_NV_optimus",
    "VK_LAYER_AMD_switchable_graphics"
};

static const char* g_enabledDeviceExtensions[] = {
    "VK_EXT_debug_marker",
    "VK_KHR_swapchain",
    "VK_EXT_descriptor_indexing"
};

GnRendererVK::GnRendererVK()
{
    m_instance = VulkanHelpers::CreateInstance();
    assert(m_instance != nullptr);
}

GnRendererVK::~GnRendererVK()
{
}

void GnRendererVK::GetAvailableAdapters(std::vector<GnAdapterInfo>& adapterInfos)
{
}

bool GnRendererVK::OpenDevice(GnAdapterId id)
{
    std::vector<VkPhysicalDevice> physicalDevices;
    VulkanHelpers::GetPhysicalDevices(m_instance, physicalDevices);

    VkPhysicalDevice selected = physicalDevices[0];

    if (id.u64[0] != 0) {
        VkPhysicalDeviceProperties props{};

        selected = nullptr;

        // Find device by ID (we use pipeline cache UUID as the ID)
        for (auto p : physicalDevices) {
            vkGetPhysicalDeviceProperties(p, &props);

            GnAdapterId deviceId;
            memcpy(deviceId.c, props.pipelineCacheUUID, sizeof(deviceId.c));

            // ID length is 16 bytes, we need to split the ID into two 64-bit integer and compare it
            if (id.u64[0] == deviceId.u64[0] && id.u64[1] == deviceId.u64[1]) {
                selected = p;
                break;
            }
        }

        if (selected == nullptr) {
            GnLog::Warn("Cannot find device ID. Using default device...");
            selected = physicalDevices[0];
        }
    }

    // Get device layers
    std::vector<VkLayerProperties> supportedLayers;
    std::vector<const char*> layerNames;

    VulkanHelpers::GetDeviceLayers(selected, supportedLayers);

    for (auto layer : g_enabledDeviceLayers) {
        for (auto& l : supportedLayers) {
            if (strncmp(l.layerName, layer, VK_MAX_DESCRIPTION_SIZE) == 0) {
                layerNames.push_back(layer);
            }
        }
    }

    // Get device extensions
    std::vector<VkExtensionProperties> supportedExtensions;
    std::vector<const char*> extNames;

    VulkanHelpers::GetDeviceExtensions(selected, supportedExtensions);

    for (auto ext : g_enabledDeviceExtensions) {
        for (auto& e : supportedExtensions) {
            if (strncmp(e.extensionName, ext, VK_MAX_DESCRIPTION_SIZE) == 0) {
                extNames.push_back(ext);
            }
        }
    }

    // Get device features
    VkPhysicalDeviceFeatures features{};
    vkGetPhysicalDeviceFeatures(selected, &features);

    // Setup queue infos
    std::vector<VkDeviceQueueCreateInfo> queueInfos;
    static const float queuePriority = 1.0f;
    uint32_t numQueue;

    vkGetPhysicalDeviceQueueFamilyProperties(selected, &numQueue, nullptr);

    for (uint32_t i = 0; i < numQueue; i++) {
        VkDeviceQueueCreateInfo queueInfo{};

        queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueInfo.queueCount = 1;
        queueInfo.queueFamilyIndex = i;
        queueInfo.pQueuePriorities = &queuePriority;
    }

    VkDeviceCreateInfo deviceInfo{};
    deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceInfo.queueCreateInfoCount = queueInfos.size();
    deviceInfo.pQueueCreateInfos = queueInfos.data();
    deviceInfo.enabledLayerCount = layerNames.size();
    deviceInfo.ppEnabledLayerNames = layerNames.data();
    deviceInfo.enabledExtensionCount = extNames.size();
    deviceInfo.ppEnabledExtensionNames = extNames.data();
    deviceInfo.pEnabledFeatures = &features;

    VkDevice device;
    if (VK_CHECK(vkCreateDevice(selected, &deviceInfo, nullptr, &device))) {
        return nullptr;
    }

    volkLoadDevice(device);

    m_device = std::static_pointer_cast<GnDevice>(std::make_shared<GnDeviceVK>(m_instance, selected, device));

    return GnRenderer::OpenDevice(id);
}

void GnRendererVK::CloseDevice()
{
    GnRenderer::CloseDevice();

    m_device = nullptr;
}
