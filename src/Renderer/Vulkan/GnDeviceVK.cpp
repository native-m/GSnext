#include "GnDeviceVK.h"

GnDeviceVK::GnDeviceVK(VkPhysicalDevice physicalDevice, VkDevice device) :
    m_physicalDevice(physicalDevice),
    m_device(device)
{
}

GnDeviceVK::~GnDeviceVK()
{
    vkDeviceWaitIdle(m_device);
    vkDestroyDevice(m_device, nullptr);
}
