#pragma once

#include <unordered_map>
#include <gsnext/GnCommon.h>
#include <gsnext/Renderer/GnAdapterInfo.h>

struct GnConfig
{
    // Adapter
    GnBackendRenderer backend;
    GnAdapterId vulkanAdapter;
    GnAdapterId d3d12Adapter;
    
    // Graphics settings
    bool gpuPaletteConv;
    bool accurateDATE;
    int resolutionScaling;
    int anisotropicFilterLevel;
    GnDithering dithering;
    GnMipmap mipmap;
    GnBlendAccuracy alphaBlendingAccuracy;

    // Advanced settings
    bool disableDepthEmulation;
    uint32_t maxVramUsage;
};
