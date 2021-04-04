#include <gsnext/Renderer/GnRenderer.h>
#include "Vulkan/GnRendererVK.h"

GnRenderer::GnRenderer()
{
}

GnRenderer::~GnRenderer()
{
}

bool GnRenderer::OpenDevice(GnAdapterId id)
{
    return false;
}

void GnRenderer::CloseDevice()
{
}

std::shared_ptr<GnRenderer> GnRenderer::Create(GnBackendRenderer backend)
{
    switch (backend) {
        case GnBackendRenderer::Vulkan:
            return std::static_pointer_cast<GnRenderer>(std::make_shared<GnRendererVK>());
    }

    return nullptr;
}
