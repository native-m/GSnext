#include <gsnext/Renderer/GnRenderer.h>
#include "Vulkan/GnRendererVK.h"

GnRenderer::GnRenderer() :
    m_outputWindowSwapchain(nullptr)
{
}

GnRenderer::~GnRenderer()
{
    Close();
}

bool GnRenderer::Open(std::shared_ptr<GnWindow>& window, const GnAdapterId& id)
{
    bool ret = OpenDevice(id);

    GnSwapchainDesc swapchain;
    GnSize2D windowSize;

    window->GetSize(windowSize);

    swapchain.bufferCount = 2;
    swapchain.width = windowSize.width;
    swapchain.height = windowSize.height;
    swapchain.format = GnDeviceFormat::B8G8R8A8_Srgb;
    swapchain.window = window;

    ret = m_device->CreateSwapchain(swapchain, &m_outputWindowSwapchain);

    Test();

    return ret;
}

void GnRenderer::Close()
{
    if (m_outputWindowSwapchain) {
        CloseDevice();
        m_device->Destroy(m_outputWindowSwapchain);
        m_outputWindowSwapchain = nullptr;
    }

    m_device = nullptr;
}

void GnRenderer::Vsync()
{
    Render();
    m_outputWindowSwapchain->Present();
}

std::shared_ptr<GnRenderer> GnRenderer::Create(GnBackendRenderer backend)
{
    switch (backend) {
        case GnBackendRenderer::Vulkan:
            return std::static_pointer_cast<GnRenderer>(std::make_shared<GnRendererVK>());
    }

    return nullptr;
}
