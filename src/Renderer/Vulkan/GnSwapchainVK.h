#pragma once

#include <gsnext/Renderer/GnSwapchain.h>
#include "VulkanHelpers.h"

class GnDeviceVK;

class GnSwapchainVK : public GnSwapchain
{
public:
    GnSwapchainVK(
        GnDeviceVK* device,
        VkSurfaceKHR surface,
        VkSwapchainKHR swapchain,
        VkQueue presentQueue,
        GnDeviceFormat format);

    ~GnSwapchainVK();

    GnPresentResult Present() override;
    uint32_t GetCurrentIndex() override;
    GnDeviceFormat GetFormat() override;

    void AcquireNextImage();
    void UpdateSwapchainIndex(uint32_t newSwapchainIndex);
    VkSurfaceKHR GetSurface() const;
    VkSwapchainKHR GetSwapchain() const;
    VkImageView GetImageView(uint32_t i) const;
    VkSemaphore GetImageAvailableSemaphore() const;
    VkSemaphore GetRenderFinishedSemaphore() const;

private:
    GnDeviceVK* m_device;
    VkSurfaceKHR m_surface;
    VkSwapchainKHR m_swapchain;
    VkQueue m_presentQueue;
    VkImage m_swapchainImages[GN_MAX_QUEUED_IMAGE];
    VkImageView m_swapchainImageViews[GN_MAX_QUEUED_IMAGE];
    VkSemaphore m_imageAvailableSemaphore;
    VkSemaphore m_renderFinishedSemaphore;
    GnDeviceFormat m_format;
    uint32_t m_bufferCount;
    uint32_t m_currentImageIndex;

    void Init();
};
