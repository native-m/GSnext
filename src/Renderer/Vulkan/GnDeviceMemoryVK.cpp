#include "GnDeviceMemoryVK.h"

GnDeviceMemoryVK::GnDeviceMemoryVK(VkDeviceMemory deviceMemory, VkDeviceSize size) :
    m_deviceMemory(deviceMemory),
    m_size(size)
{
}

GnDeviceMemoryVK::~GnDeviceMemoryVK()
{
}

size_t GnDeviceMemoryVK::GetSize() const
{
    return static_cast<size_t>(m_size);
}

VkDeviceMemory GnDeviceMemoryVK::GetHandle() const
{
    return m_deviceMemory;
}
