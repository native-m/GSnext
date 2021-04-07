#pragma once

#include <gsnext/Renderer/GnDevice.h>
#include <gsnext/GnWindow.h>
#include <memory>
#include <unordered_set>
#include "VulkanHelpers.h"

class GnDeviceVK : public GnDevice
{
public:
    GnDeviceVK(VkInstance instance, VkPhysicalDevice physicalDevice, VkDevice device);
    ~GnDeviceVK();

    bool CreateTexture(
        const GnTextureDesc& desc,
        GnTexture** texture) override;

    bool CreateDrawBuffer(
        const GnDrawBufferDesc& desc,
        GnDrawBuffer** drawBuffer) override;

    bool CreateSwapchain(const GnSwapchainDesc& desc, GnSwapchain** swapchain) override;

    void ExecuteDrawBuffer(GnDrawBuffer* drawBuffer) override;

    void Destroy(GnTexture* texture) override;
    void Destroy(GnDrawBuffer* drawBuffer) override;
    void Destroy(GnSwapchain* swapchain) override;

    GnMemoryTypeBits GetSupportedMemoryType() override;

    GnDeviceFormat ConvertPSM(GnPixelStorageMode psm) override;
    
    VkInstance GetInstance() const;
    VkDevice GetHandle() const;
    void GetQueue(GnCommandQueue queueType, VkQueue* queue, uint32_t* index);
    VkCommandPool GetDrawCommandPool() const;
    VkCommandPool GetTransferCommandPool() const;

private:
    struct CommandQueue
    {
        uint32_t queueFamilyIndex;
        VkQueue cmdQueue;
    };

    VkInstance m_instance;
    VkPhysicalDevice m_physicalDevice;
    VkDevice m_device;
    std::unordered_map<GnCommandQueue, CommandQueue> m_cmdQueues;
    VkCommandPool m_drawCmdPool;
    VkCommandPool m_xferCmdPool;

    bool m_asyncComputeSupport = false;
    bool m_asyncTransferSupport = false;
    bool m_32bitFloatZBufferFmt = false;
    bool m_24bitZBuffer8bitStencilFmt = false;
    bool m_24bitZBufferPackedFmt = false;

    GnMemoryTypeBits m_supportedMemoryType;

    void InitFeatures();
    void InitQueue();
    void InitCommandPools();

    VkSurfaceKHR CreateSurface(const GnSwapchainDesc& desc);
};
