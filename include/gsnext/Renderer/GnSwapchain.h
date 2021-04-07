#pragma once

#include <gsnext/Renderer/GnRendererTypes.h>

class GnSwapchain
{
public:
    virtual ~GnSwapchain() { }

    virtual GnPresentResult Present() = 0;
    virtual uint32_t GetCurrentIndex() = 0;
    virtual GnDeviceFormat GetFormat() = 0;

protected:
    GnSwapchain() { }
};
