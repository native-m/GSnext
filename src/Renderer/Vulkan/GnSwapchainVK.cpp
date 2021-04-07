#include "GnSwapchainVK.h"
#include "GnDeviceVK.h"
#include <gsnext/GnLog.h>

GnSwapchainVK::GnSwapchainVK(
    GnDeviceVK* device,
    VkSurfaceKHR surface,
    VkSwapchainKHR swapchain,
    VkQueue presentQueue,
    GnDeviceFormat format) :
    m_device(device),
    m_surface(surface),
    m_swapchain(swapchain),
    m_presentQueue(presentQueue),
    m_swapchainImages{ VK_NULL_HANDLE },
    m_swapchainImageViews{ VK_NULL_HANDLE },
    m_imageAvailableSemaphore(VulkanHelpers::CreateGpuSemaphore(device->GetHandle())),
    m_renderFinishedSemaphore(VulkanHelpers::CreateGpuSemaphore(device->GetHandle())),
    m_format(format),
    m_bufferCount(0),
    m_currentImageIndex(0)
{
    Init();
}

GnSwapchainVK::~GnSwapchainVK()
{
    VkDevice handle = m_device->GetHandle();

    vkDeviceWaitIdle(handle);

    for (uint32_t i = 0; i < m_bufferCount; i++) {
        vkDestroyImageView(handle, m_swapchainImageViews[i], nullptr);
    }

    vkDestroySemaphore(handle, m_imageAvailableSemaphore, nullptr);
    vkDestroySemaphore(handle, m_renderFinishedSemaphore, nullptr);
    vkDestroySwapchainKHR(handle, m_swapchain, nullptr);
    vkDestroySurfaceKHR(m_device->GetInstance(), m_surface, nullptr);
}

GnPresentResult GnSwapchainVK::Present()
{
    VkPipelineStageFlags waitStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    VkSubmitInfo submitInfo{};

    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = &m_imageAvailableSemaphore;
    submitInfo.pWaitDstStageMask = &waitStageMask;
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = &m_renderFinishedSemaphore;

    VkResult result = vkQueueSubmit(m_presentQueue, 1, &submitInfo, VK_NULL_HANDLE);

    if (VK_CHECK(result)) {
        GnLog::Error("Cannot submit semaphores");
        return GnPresentResult::Error;
    }

    VkPresentInfoKHR presentInfo{};

    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = &m_renderFinishedSemaphore;
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = &m_swapchain;
    presentInfo.pImageIndices = &m_currentImageIndex;

    result = vkQueuePresentKHR(m_presentQueue, &presentInfo);

    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        return GnPresentResult::SurfaceResized;
    }
    else if (result < 0) {
        return GnPresentResult::Error;
    }

    AcquireNextImage();

    return GnPresentResult::Ok;
}

uint32_t GnSwapchainVK::GetCurrentIndex()
{
    return m_currentImageIndex;
}

GnDeviceFormat GnSwapchainVK::GetFormat()
{
    return m_format;
}

void GnSwapchainVK::AcquireNextImage()
{
    vkAcquireNextImageKHR(
        m_device->GetHandle(),
        m_swapchain,
        UINT64_MAX,
        m_imageAvailableSemaphore,
        VK_NULL_HANDLE,
        &m_currentImageIndex);
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

VkImageView GnSwapchainVK::GetImageView(uint32_t i) const
{
    return m_swapchainImageViews[i];
}

VkSemaphore GnSwapchainVK::GetImageAvailableSemaphore() const
{
    return m_imageAvailableSemaphore;
}

VkSemaphore GnSwapchainVK::GetRenderFinishedSemaphore() const
{
    return m_renderFinishedSemaphore;
}

void GnSwapchainVK::Init()
{
    VkResult result;
    VkImageViewCreateInfo imgViewInfo{};
    VkDevice device = m_device->GetHandle();
    VkImageMemoryBarrier imageBarrier{};
    VkQueue queue = VK_NULL_HANDLE;
    uint32_t queueIndex = 0;
    std::vector<VkImageMemoryBarrier> imageBarriers;

    m_device->GetQueue(GnCommandQueue::Direct, &queue, &queueIndex);

    imgViewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    imgViewInfo.image = VK_NULL_HANDLE;
    imgViewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    imgViewInfo.format = VulkanHelpers::ConvertFormat(m_format);
    imgViewInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    imgViewInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    imgViewInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    imgViewInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    imgViewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    imgViewInfo.subresourceRange.baseMipLevel = 0;
    imgViewInfo.subresourceRange.levelCount = 1;
    imgViewInfo.subresourceRange.baseArrayLayer = 0;
    imgViewInfo.subresourceRange.layerCount = 1;

    imageBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    imageBarrier.srcAccessMask = 0;
    imageBarrier.dstAccessMask = 0;
    imageBarrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    imageBarrier.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    imageBarrier.srcQueueFamilyIndex = queueIndex;
    imageBarrier.dstQueueFamilyIndex = queueIndex;
    imageBarrier.image = VK_NULL_HANDLE;
    imageBarrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    imageBarrier.subresourceRange.baseMipLevel = 0;
    imageBarrier.subresourceRange.levelCount = 1;
    imageBarrier.subresourceRange.baseArrayLayer = 0;
    imageBarrier.subresourceRange.layerCount = 1;
    
    result = vkGetSwapchainImagesKHR(device, m_swapchain, &m_bufferCount, nullptr);
    assert(!VK_CHECK(result));

    result = vkGetSwapchainImagesKHR(device, m_swapchain, &m_bufferCount, m_swapchainImages);
    assert(!VK_CHECK(result));

    for (uint32_t i = 0; i < m_bufferCount; i++) {
        imgViewInfo.image = m_swapchainImages[i];

        if (VK_CHECK(vkCreateImageView(device, &imgViewInfo, nullptr, &m_swapchainImageViews[i]))) {
            GnLog::Error("Cannot create image view for swapchain");
            assert(0);
        }

        imageBarrier.image = imgViewInfo.image;

        imageBarriers.push_back(imageBarrier);
    }

    // Swapchain image layout pre-transition

    VkCommandBuffer cmdBuffer;
    VkCommandBufferAllocateInfo cmdBufferInfo{};

    cmdBufferInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    cmdBufferInfo.commandPool = m_device->GetDrawCommandPool();
    cmdBufferInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cmdBufferInfo.commandBufferCount = 1;

    result = vkAllocateCommandBuffers(device, &cmdBufferInfo, &cmdBuffer);
    assert(!VK_CHECK(result));

    VkCommandBufferBeginInfo beginInfo{};

    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(cmdBuffer, &beginInfo);

    vkCmdPipelineBarrier(
        cmdBuffer,
        VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
        VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
        0,
        0,
        nullptr,
        0,
        nullptr,
        imageBarriers.size(),
        imageBarriers.data());

    vkEndCommandBuffer(cmdBuffer);

    VkSubmitInfo submitInfo{};

    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &cmdBuffer;

    vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE);
    vkDeviceWaitIdle(device);

    vkFreeCommandBuffers(device, cmdBufferInfo.commandPool, 1, &cmdBuffer);

    AcquireNextImage();

    (void)result;
}
