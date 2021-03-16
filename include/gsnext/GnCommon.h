#pragma once

#include <cstdint>

#define GN_MAX_CHAR 256

enum class GnBackendRenderer
{
    Vulkan,
    D3D12
};

enum class GnDithering
{
    Off,        // Disable dithering
    Unscaled,   // Unscaled dithering
    Scaled,     // Scaled dithering
    Custom      // Use custom dithering matrix
};

enum class GnMipmap
{
    Off,        // Disable mipmapping
    Automatic,  // Automatically sets mipmapping level based on the game
    Low,        // Basic (partial) mipmapping
    PS2,        // Completely emulates PS2 GS mipmapping function, maybe slow
    Full,       // Same like PS2 mipmapping, but uses up to 8 mipmap level (6 on PS2), the slowest
    Custom      // Use custom mipmapping level
};

enum class GnBlendAccuracy
{
    Off,        // Disable alpha blending emulation
    Low,        // Partially emulates GS alpha blending, the fastest
    Medium,     // 
    High,       // Completely emulates GS alpha blending, the slowest
};

enum class GnPrimTopology
{
    Point,
    Line,
    LineStrip,
    Triangle,
    TriangleStrip,
    TriangleFan,
    Sprite,
    Reserved
};

enum class GnAlphaTestMethod
{
    Never,
    Always,
    Less,
    LessEqual,
    Equal,
    GreaterEqual,
    Greater,
    NotEqual
};

enum class GnAlphaTestFail
{
    Keep,
    FbOnly,
    ZbOnly,
    RgbOnly
};

enum class GnDepthTestMethod
{
    Never,
    Always,
    GreaterEqual,
    Greater
};

enum class GnFormat
{
    PSMCT32 = 0x00,
    PSMCT24 = 0x01,
    PSMCT16 = 0x02,
    PSMCT16S = 0x0a,
    PSMT8 = 0x13,
    PSMT4 = 0x14,
    PSMT8H = 0x1B,
    PSMT4HL = 0x24,
    PSMT4HH = 0x2C,
    PSMZ32 = 0x30,
    PSMZ24 = 0x31,
    PSMZ16 = 0x32,
    PSMZ16S = 0x3a,
};

enum class GnTextureFunction
{
    Modulate,
    Decal,
    Highlight,
    Highlight2
};

enum class GnTextureWrapMode
{
    Repeat,
    Clamp,
    RegionClamp,
    RegionRepeat
};