#pragma once

#include <gsnext/Renderer/GnDrawBuffer.h>
#include "GnDeviceVK.h"
#include "VulkanHelpers.h"

class GnDrawBufferVK : public GnDrawBuffer
{
public:
    GnDrawBufferVK(GnDeviceVK* parentDevice);
    ~GnDrawBufferVK();

    void Begin() override;
    void End() override;
    void Flush() override;

private:
    GnDeviceVK* m_parentDevice;

    VkCommandPool m_cmdPool;
    VkCommandBuffer m_drawCmdBuffer;

    VkBuffer m_vertexBuffer;
    VkDeviceMemory m_vtxBufDeviceMem;
    VkDeviceSize m_vtxBufMemBindingOffset;

    void Init();
};
