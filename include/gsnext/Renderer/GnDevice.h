#pragma once

#include <gsnext/GnWindow.h>
#include <gsnext/GnConfig.h>
#include <gsnext/Renderer/GnAdapterInfo.h>
#include <gsnext/Renderer/GnDeviceMemory.h>
#include <gsnext/Renderer/GnBuffer.h>
#include <gsnext/Renderer/GnTexture.h>
#include <gsnext/Renderer/GnRenderPass.h>
#include <gsnext/Renderer/GnFrameBuffer.h>
#include <gsnext/Renderer/GnGraphicsPipeline.h>
#include <gsnext/Renderer/GnCommandBuffer.h>
#include <gsnext/Renderer/GnCommandPool.h>

typedef uint32_t GnMemoryTypeBits;
typedef uint32_t GnBufferUsageBits;

enum class GnCommandQueue;
enum class GnFenceType;

struct GnMemoryType;
struct GnBufferUsage;
struct GnMemoryAllocationDesc;
struct GnMemoryBindingDesc;
struct GnDeviceMemory;
struct GnBufferDesc;
struct GnTextureDesc;
struct GnRenderPassDesc;
struct GnFramebufferDesc;
struct GnGraphicsPipelineDesc;
struct GnCommandPoolDesc;
struct GnCommandBufferDesc;
struct GnSwapchainDesc;
struct GnFenceDesc;

class GnDevice
{
public:
    virtual ~GnDevice() { }

    virtual bool Initialize(GnAdapterId id) = 0;
    virtual void AllocateMemory(const GnMemoryAllocationDesc& desc, GnDeviceMemory** deviceMemory) = 0;
    virtual bool CreateBuffer(const GnBufferDesc& desc, const GnMemoryBindingDesc& memoryBinding, GnBuffer** buffer) = 0;
    virtual bool CreateTexture(const GnTextureDesc& desc, const GnMemoryBindingDesc& memoryBinding, GnTexture** texture) = 0;
    virtual bool CreateRenderPass(const GnRenderPassDesc& desc, GnRenderPass** renderPass) = 0;
    virtual bool CreateFramebuffer(const GnFramebufferDesc& desc, GnFramebuffer** framebuffer) = 0;
    virtual bool CreateGraphicsPipeline(const GnGraphicsPipelineDesc& desc, GnGraphicsPipeline** graphicsPipeline) = 0;
    virtual bool CreateCommandPool(const GnCommandPoolDesc& desc, GnCommandPool** cmdPool) = 0;
    virtual bool CreateCommandBuffer(GnCommandPool* cmdPool, uint32_t count, GnCommandBuffer** cmdBuffer) = 0;
    virtual bool CreateSwapchain(const GnSwapchainDesc& desc) = 0;
    virtual bool CreateFence(const GnFenceDesc& desc) = 0;
    virtual void ExecuteCommandBuffer(GnCommandQueue commandQueue) = 0;
    virtual void QueueWaitIdle(GnCommandQueue commandQueue) = 0;

    virtual void BeginImGui() = 0;
    virtual void EndImGui() = 0;
    virtual void RenderImGui() = 0;

    virtual void FreeMemory(GnDeviceMemory* deviceMemory) = 0;
    virtual void Destroy() = 0;

protected:
    GnDevice() { }
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
    SemaphoreSync   // GPU -> GPU sync (between command buffer execution)
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

struct GnBufferUsage
{
    enum
    {
        TransferSrc,
        TransferDst,
        VertexBuffer
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

struct GnBufferDesc
{
    size_t size;
    GnBufferUsageBits usage;
};

struct GnCommandPoolDesc
{
    GnCommandQueue targetCmdQueue;
    bool canReset;
};

struct GnShaderProgram
{
    size_t size;
    const uint8_t* shaderBytecode;
    const char* entryPoint;
};

struct GnGraphicsPipelineDesc
{
    GnShaderProgram VS;
    GnShaderProgram PS;
};

struct GnFenceDesc
{
    GnFenceType fenceType;
    bool signaled;
};
