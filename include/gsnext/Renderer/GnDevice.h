#pragma once

#include <gsnext/Renderer/GnRendererTypes.h>
#include <gsnext/Renderer/GnAdapterInfo.h>
#include <gsnext/Renderer/GnTexture.h>
#include <gsnext/Renderer/GnDrawBuffer.h>
#include <gsnext/Renderer/GnSwapchain.h>

class GnDevice
{
public:
    virtual ~GnDevice() { }

    virtual bool CreateTexture(
        const GnTextureDesc& desc,
        GnTexture** texture) = 0;

    virtual bool CreateDrawBuffer(
        const GnDrawBufferDesc& desc,
        GnDrawBuffer** drawBuffer) = 0;

    virtual bool CreateSwapchain(const GnSwapchainDesc& desc, GnSwapchain** swapchain) = 0;

    virtual void ExecuteDrawBuffer(GnDrawBuffer* drawBuffer) = 0;
    virtual void Present(GnSwapchain* swapchain) = 0;

    virtual void Destroy(GnTexture* texture) = 0;
    virtual void Destroy(GnDrawBuffer* drawBuffer) = 0;

    virtual GnMemoryTypeBits GetSupportedMemoryType() = 0;

    virtual GnDeviceFormat ConvertPSM(GnPixelStorageMode psm) = 0;

protected:
    GnDevice() { }
};
