#pragma once

#include <gsnext/GnCommon.h>
#include <gsnext/GnWindow.h>

class GnDevice;
class GnDeviceMemory;
class GnTexture;

typedef uint32_t GnMemoryTypeBits;
typedef uint32_t GnBufferUsageBits;

enum class GnDeviceFormat
{
    Unknown,

    // Equivalent to PSMCT32/PSMCT24
    // Usually used for swapchain images
    R8G8B8A8_Unorm,
    R8G8B8A8_Srgb,
    R8G8B8X8_Unorm,
    B8G8R8A8_Unorm,
    B8G8R8A8_Srgb,

    // Equivalent to PSMCT16(S)
    R5G5B5A1_Unorm,

    // Equivalent to PSM8T(H)
    R8_Unorm,

    // Used for vertex list
    R32G32_Uint,
    R32G32B32A32_Float,

    // Depth buffer
    D32_Float,
    D24_X8_Unorm,
    D24_S8_Unorm,
    D16_Unorm
};

enum class GnCommandQueue
{
    Direct,         // Graphics, compute and transfer queue
    Compute,        // Compute and transfer queue
    Transfer        // Transfer queue
};

enum class GnFenceType
{
    HostSync,       // Host -> GPU sync
    SemaphoreSync   // GPU -> GPU sync
};

struct GnMemoryType
{
    enum
    {
        DeviceLocal = 1,
        HostVisible = 1 << 2,
        HostCoherent = 1 << 3
    };
};

struct GnMemoryAllocationDesc
{
    size_t size;
    GnMemoryTypeBits memoryType;
};

struct GnMemoryBindingDesc
{
    GnDeviceMemory* deviceMemory;
    size_t offset;
};

struct GnTextureDesc
{
    GnDeviceFormat format;
    uint32_t width;
    uint32_t height;
};

struct GnDrawBufferDesc
{
};

struct GnSwapchainDesc
{
    uint32_t bufferCount;
    uint32_t width;
    uint32_t height;
    GnDeviceFormat format;
    std::shared_ptr<GnWindow> window;
};
