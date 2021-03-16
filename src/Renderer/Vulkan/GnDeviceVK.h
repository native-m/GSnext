#pragma once

#include <gsnext/Renderer/GnDevice.h>
#include <memory>
#include "VulkanHelpers.h"

class GnDeviceVK : public GnDevice
{
public:
    GnDeviceVK(VkPhysicalDevice physicalDevice, VkDevice device);
    ~GnDeviceVK();

    std::unique_ptr<GnDevice> Create();

private:
    VkPhysicalDevice m_physicalDevice;
    VkDevice m_device;
};
