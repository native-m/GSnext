#pragma once

#include <gsnext/Renderer/GnRenderer.h>
#include "VulkanHelpers.h"

class GnRendererVK : public GnRenderer
{
public:
    GnRendererVK();
    virtual ~GnRendererVK();

    void GetAvailableAdapters(std::vector<GnAdapterInfo>& adapterInfos) override;
    bool OpenDevice(const GnAdapterId& id) override;
    void Test() override;
    void Render() override;
    void CloseDevice() override;

private:
    VkInstance m_instance;
    VkRenderPass m_renderPass = VK_NULL_HANDLE;
    VkFramebuffer m_framebuffer[2] { VK_NULL_HANDLE };
    VkCommandBuffer m_cmdBuffer[2] { VK_NULL_HANDLE };
};
