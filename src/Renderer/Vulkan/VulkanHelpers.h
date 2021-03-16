#pragma once

#ifdef _WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#endif

#include <cassert>
#include <vector>
#include "volk.h"

#define VK_CHECK(x) \
    ((x) < VK_SUCCESS)

struct VulkanHelpers
{
    static VkInstance CreateInstance();
    static void GetPhysicalDevices(VkInstance instance, std::vector<VkPhysicalDevice>& physicalDevices);
    static void DestroyInstance(VkInstance instance);
};
