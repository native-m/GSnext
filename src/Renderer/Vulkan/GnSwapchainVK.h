#pragma once

#include <gsnext/Renderer/GnSwapchain.h>
#include "VulkanHelpers.h"

class GnSwapchainVK : public GnSwapchain
{
public:
    GnSwapchainVK(VkSurfaceKHR surface, VkSwapchainKHR swapchain);
    ~GnSwapchainVK();

    void UpdateSwapchainIndex(uint32_t newSwapchainIndex);
    VkSurfaceKHR GetSurface() const;
    VkSwapchainKHR GetSwapchain() const;

private:
    VkSurfaceKHR m_surface;
    VkSwapchainKHR m_swapchain;

    uint32_t m_currentImageIndex;
};
