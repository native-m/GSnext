#include "GnRendererVK.h"
#include "GnDeviceVK.h"
#include "GnSwapchainVK.h"

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
    VulkanHelpers::DestroyInstance(m_instance);
}

void GnRendererVK::GetAvailableAdapters(std::vector<GnAdapterInfo>& adapterInfos)
{
}

bool GnRendererVK::OpenDevice(const GnAdapterId& id)
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

        queueInfos.push_back(queueInfo);
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
        return false;
    }

    volkLoadDevice(device);

    m_device = std::static_pointer_cast<GnDevice>(std::make_shared<GnDeviceVK>(m_instance, selected, device));

    return true;
}

void GnRendererVK::Test()
{
    std::shared_ptr<GnDeviceVK> vkdevice = std::static_pointer_cast<GnDeviceVK>(m_device);
    VkDevice device = vkdevice->GetHandle();
    VkResult result;
    VkRenderPassCreateInfo renderpassInfo{};
    VkAttachmentDescription attachmentDesc{};
    VkAttachmentReference attRef{};
    VkSubpassDescription subpass{};
    VkQueue queue;
    GnSwapchainVK* swapchain = static_cast<GnSwapchainVK*>(m_outputWindowSwapchain);

    vkdevice->GetQueue(GnCommandQueue::Direct, &queue, nullptr);

    attachmentDesc.format = VK_FORMAT_B8G8R8A8_SRGB;
    attachmentDesc.samples = VK_SAMPLE_COUNT_1_BIT;
    attachmentDesc.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachmentDesc.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachmentDesc.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachmentDesc.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachmentDesc.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachmentDesc.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    attRef.attachment = 0;
    attRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &attRef;

    renderpassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderpassInfo.attachmentCount = 1;
    renderpassInfo.pAttachments = &attachmentDesc;
    renderpassInfo.subpassCount = 1;
    renderpassInfo.pSubpasses = &subpass;

    result = vkCreateRenderPass(device, &renderpassInfo, nullptr, &m_renderPass);
    assert(!VK_CHECK(result));

    VkFramebufferCreateInfo fbInfo{};

    fbInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    fbInfo.renderPass = m_renderPass;
    fbInfo.attachmentCount = 1;
    fbInfo.width = 640;
    fbInfo.height = 480;
    fbInfo.layers = 1;

    for (uint32_t i = 0; i < 2; i++) {
        VkImageView imageView = swapchain->GetImageView(i);

        fbInfo.pAttachments = &imageView;

        result = vkCreateFramebuffer(device, &fbInfo, nullptr, &m_framebuffer[i]);
        assert(!VK_CHECK(result));
    }

    VkCommandBufferAllocateInfo cmdBufferInfo{};

    cmdBufferInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    cmdBufferInfo.commandPool = vkdevice->GetDrawCommandPool();
    cmdBufferInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cmdBufferInfo.commandBufferCount = 2;

    result = vkAllocateCommandBuffers(device, &cmdBufferInfo, m_cmdBuffer);
    assert(!VK_CHECK(result));

    for (uint32_t i = 0; i < 2; i++) {
        VkCommandBuffer cmdBuffer = m_cmdBuffer[i];
        VkCommandBufferBeginInfo beginInfo{};

        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        vkBeginCommandBuffer(cmdBuffer, &beginInfo);

        VkRenderPassBeginInfo rpBegin{};
        VkClearValue clearValue{};

        clearValue.color.float32[0] = 1.0f;
        clearValue.color.float32[1] = 0.0f;
        clearValue.color.float32[2] = 0.0f;
        clearValue.color.float32[3] = 1.0f;

        rpBegin.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        rpBegin.renderPass = m_renderPass;
        rpBegin.framebuffer = m_framebuffer[i];
        rpBegin.clearValueCount = 1;
        rpBegin.pClearValues = &clearValue;
        rpBegin.renderArea.offset.x = 0;
        rpBegin.renderArea.offset.y = 0;
        rpBegin.renderArea.extent.width = 640;
        rpBegin.renderArea.extent.height = 480;

        vkCmdBeginRenderPass(cmdBuffer, &rpBegin, VK_SUBPASS_CONTENTS_INLINE);
        vkCmdEndRenderPass(cmdBuffer);

        vkEndCommandBuffer(cmdBuffer);
    }

    VkSubmitInfo submitInfo{};

    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 2;
    submitInfo.pCommandBuffers = m_cmdBuffer;

    vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE);
    vkDeviceWaitIdle(device);
}

void GnRendererVK::Render()
{
}

void GnRendererVK::CloseDevice()
{
    VkDevice device = std::static_pointer_cast<GnDeviceVK>(m_device)->GetHandle();

    for (auto& fb : m_framebuffer) {
        vkDestroyFramebuffer(device, fb, nullptr);
    }

    vkDestroyRenderPass(device, m_renderPass, nullptr);
}
