#pragma once

#include <gsnext/Renderer/GnRenderer.h>
#include "VulkanHelpers.h"

class GnRendererVK : public GnRenderer
{
public:
    GnRendererVK();
    virtual ~GnRendererVK();

    void GetAvailableAdapters(std::vector<GnAdapterInfo>& adapterInfos) override;
    bool OpenDevice(GnAdapterId id) override;
    void CloseDevice() override;

private:
    VkInstance m_instance;
};
