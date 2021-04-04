#pragma once

#ifdef _WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#endif

#include <gsnext/GnCommon.h>
#include <gsnext/Renderer/GnRendererTypes.h>
#include "volk.h"

#define VK_CHECK(x) \
    ((x) < VK_SUCCESS)

struct VulkanHelpers
{
    static VkInstance CreateInstance();
    static void GetPhysicalDevices(VkInstance instance, std::vector<VkPhysicalDevice>& physicalDevices);
    static void GetDeviceLayers(VkPhysicalDevice physicalDevice, std::vector<VkLayerProperties>& layers);
    static void GetDeviceExtensions(VkPhysicalDevice physicalDevice, std::vector<VkExtensionProperties>& extensions);
    static void GetDeviceQueueFamilies(VkPhysicalDevice physicalDevice, std::vector<VkQueueFamilyProperties>& queueFamilies);
    static void DestroyInstance(VkInstance instance);

    inline static VkFormat ConvertFormat(GnDeviceFormat fmt);
};

inline VkFormat VulkanHelpers::ConvertFormat(GnDeviceFormat fmt)
{
    switch (fmt) {
        case GnDeviceFormat::R8G8B8A8_Srgb:
            return VK_FORMAT_R8G8B8A8_SRGB;
        case GnDeviceFormat::R8G8B8A8_Unorm:
            return VK_FORMAT_R8G8B8A8_UNORM;
        case GnDeviceFormat::B8G8R8A8_Srgb:
            return VK_FORMAT_B8G8R8A8_SRGB;
        case GnDeviceFormat::B8G8R8A8_Unorm:
            return VK_FORMAT_B8G8R8A8_UNORM;
        case GnDeviceFormat::R5G5B5A1_Unorm:
            return VK_FORMAT_R5G5B5A1_UNORM_PACK16;
        case GnDeviceFormat::R8_Unorm:
            return VK_FORMAT_R8_UNORM;
        case GnDeviceFormat::R32G32_Uint:
            return VK_FORMAT_R32G32_UINT;
        case GnDeviceFormat::R32G32B32A32_Float:
            return VK_FORMAT_R32G32B32A32_SFLOAT;
    }

    return VK_FORMAT_UNDEFINED;
}
