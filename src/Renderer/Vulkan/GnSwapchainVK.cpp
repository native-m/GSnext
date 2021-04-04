#include "GnSwapchainVK.h"

GnSwapchainVK::GnSwapchainVK(VkSurfaceKHR surface, VkSwapchainKHR swapchain) :
    m_surface(surface),
    m_swapchain(swapchain)
{
}

GnSwapchainVK::~GnSwapchainVK()
{
}

void GnSwapchainVK::UpdateSwapchainIndex(uint32_t newSwapchainIndex)
{
    m_currentImageIndex = newSwapchainIndex;
}

VkSurfaceKHR GnSwapchainVK::GetSurface() const
{
    return m_surface;
}

VkSwapchainKHR GnSwapchainVK::GetSwapchain() const
{
    return m_swapchain;
}
