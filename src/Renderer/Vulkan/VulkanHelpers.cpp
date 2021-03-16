#include "VulkanHelpers.h"

static const char* g_instanceLayers[] = {
    "VK_LAYER_KHRONOS_validation"
};

// We expect the platform to support these extensions
static const char* g_instanceExtensions[] = {
    "VK_KHR_surface",
    "VK_KHR_win32_surface"
};

VkInstance VulkanHelpers::CreateInstance()
{
    if (VK_CHECK(volkInitialize())) {
        return nullptr;
    }

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "GSnext";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "GSnext Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = volkGetInstanceVersion();

    if (appInfo.apiVersion == 0) {
        return nullptr;
    }

    VkInstanceCreateInfo instanceInfo{};
    instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceInfo.pApplicationInfo = &appInfo;
    instanceInfo.enabledLayerCount = 1;
    instanceInfo.ppEnabledLayerNames = g_instanceLayers;
    instanceInfo.enabledExtensionCount = 2;
    instanceInfo.ppEnabledExtensionNames = g_instanceExtensions;

    VkInstance instance = VK_NULL_HANDLE;
    if (VK_CHECK(vkCreateInstance(&instanceInfo, nullptr, &instance))) {
        return nullptr;
    }

    return instance;
}

void VulkanHelpers::GetPhysicalDevices(VkInstance instance, std::vector<VkPhysicalDevice>& physicalDevices)
{
    uint32_t numPhysicalDevices;
    VkResult result = vkEnumeratePhysicalDevices(instance, &numPhysicalDevices, nullptr); // get number of physical devices
    assert(!VK_CHECK(result));

    physicalDevices.resize(numPhysicalDevices);
    result = vkEnumeratePhysicalDevices(instance, &numPhysicalDevices, physicalDevices.data()); // retrieve the list of physical devices
    assert(!VK_CHECK(result));
}

void VulkanHelpers::DestroyInstance(VkInstance instance)
{
    vkDestroyInstance(instance, nullptr);
}
