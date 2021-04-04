#pragma once

#include <gsnext/Renderer/GnRendererTypes.h>

class GnSwapchain
{
public:
    virtual ~GnSwapchain() { }

    virtual uint32_t GetCurrentIndex() = 0;

protected:
    GnSwapchain() { }
};
