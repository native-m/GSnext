#pragma once

#include <gsnext/Renderer/GnDeviceMemory.h>
#include "VulkanHelpers.h"

class GnDeviceMemoryVK : public GnDeviceMemory
{
public:
    GnDeviceMemoryVK(VkDeviceMemory deviceMemory, VkDeviceSize size);
    ~GnDeviceMemoryVK();

    size_t GetSize() const override;
    VkDeviceMemory GetHandle() const;

private:
    VkDeviceMemory m_deviceMemory;
    VkDeviceSize m_size;
};
