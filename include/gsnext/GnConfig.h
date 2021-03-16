#pragma once

#include <unordered_map>
#include <gsnext/GnCommon.h>

struct GnConfigData
{
    GnBackendRenderer backend;
    char adapterId[8];
    bool gpuPaletteConv;
    bool accurateDATE;
    int resolutionScaling;
    int anisotropicFilterLevel;
    GnDithering dithering;
    GnMipmap mipmap;
    GnBlendAccuracy alphaBlendingAccuracy;

    // Advanced settings
    bool disableDepth;
};
