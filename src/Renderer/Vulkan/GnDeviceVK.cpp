#include "GnDeviceVK.h"
#include "GnSwapchainVK.h"
#include <gsnext/GnLog.h>

#define GN_VK_DIRECT_COMMAND_QUEUE (VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT)

GnDeviceVK::GnDeviceVK(VkInstance instance, VkPhysicalDevice physicalDevice, VkDevice device) :
    m_instance(instance),
    m_physicalDevice(physicalDevice),
    m_device(device)
{
    InitFeatures();
    InitQueue();
}

GnDeviceVK::~GnDeviceVK()
{
    vkDeviceWaitIdle(m_device);
    vkDestroyDevice(m_device, nullptr);
    VulkanHelpers::DestroyInstance(m_instance);
}

bool GnDeviceVK::CreateTexture(const GnTextureDesc& desc, GnTexture** texture)
{
    return false;
}

bool GnDeviceVK::CreateDrawBuffer(const GnDrawBufferDesc& desc, GnDrawBuffer** drawBuffer)
{
    return false;
}

bool GnDeviceVK::CreateSwapchain(const GnSwapchainDesc& desc, GnSwapchain** swapchain)
{
    assert(swapchain != nullptr);
    VkSurfaceKHR surface = CreateSurface(desc);
    
    if (surface == VK_NULL_HANDLE) {
        return false;
    }

    uint32_t surfaceFormatCount = 0;
    uint32_t surfaceFormatIndex = 0;
    std::vector<VkSurfaceFormatKHR> surfaceFormats;

    vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicalDevice, surface, &surfaceFormatCount, nullptr);
    surfaceFormats.resize(surfaceFormatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicalDevice, surface, &surfaceFormatCount, surfaceFormats.data());

    bool formatSupported = false;
    uint32_t i = 0;
    VkFormat swapchainFormat = VulkanHelpers::ConvertFormat(desc.format);

    for (auto& f : surfaceFormats) {
        if (swapchainFormat == f.format) {
            surfaceFormatIndex = i;
            formatSupported = true;
            break;
        }

        i++;
    }

    if (!formatSupported) {
        GnLog::Critical("The image format is not supported by the surface");
        return false;
    }

    VkSwapchainCreateInfoKHR swapchainInfo{};
    VkSwapchainKHR vkswapchain;

    swapchainInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapchainInfo.surface = surface;
    swapchainInfo.minImageCount = desc.bufferCount;
    swapchainInfo.imageFormat = surfaceFormats[surfaceFormatIndex].format;
    swapchainInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    swapchainInfo.imageExtent.width = desc.width;
    swapchainInfo.imageExtent.height = desc.height;
    swapchainInfo.imageArrayLayers = 1;
    swapchainInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    swapchainInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    swapchainInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    swapchainInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swapchainInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR;
    swapchainInfo.clipped = VK_TRUE;
    swapchainInfo.oldSwapchain = VK_NULL_HANDLE;

    if (VK_CHECK(vkCreateSwapchainKHR(m_device, &swapchainInfo, nullptr, &vkswapchain))) {
        return false;
    }

    *swapchain = new GnSwapchainVK(surface, vkswapchain);

    return true;
}

void GnDeviceVK::ExecuteDrawBuffer(GnDrawBuffer* drawBuffer)
{
}

void GnDeviceVK::Present(GnSwapchain* swapchain)
{
    GnSwapchainVK* vkswapchain = static_cast<GnSwapchainVK*>(swapchain);
}

void GnDeviceVK::Destroy(GnTexture* texture)
{
}

void GnDeviceVK::Destroy(GnDrawBuffer* drawBuffer)
{
}

GnMemoryTypeBits GnDeviceVK::GetSupportedMemoryType()
{
    return m_supportedMemoryType;
}

GnDeviceFormat GnDeviceVK::ConvertPSM(GnPixelStorageMode psm)
{
    switch (psm) {
        case GnPixelStorageMode::PSMCT32:
            return GnDeviceFormat::R8G8B8A8_Unorm;
        case GnPixelStorageMode::PSMCT24:
            return GnDeviceFormat::R8G8B8X8_Unorm;
        case GnPixelStorageMode::PSMCT16:
        case GnPixelStorageMode::PSMCT16S:
            return GnDeviceFormat::R5G5B5A1_Unorm;
        case GnPixelStorageMode::PSMT8:
        case GnPixelStorageMode::PSMT8H:
        case GnPixelStorageMode::PSMT4:
        case GnPixelStorageMode::PSMT4HH:
        case GnPixelStorageMode::PSMT4HL:
            return GnDeviceFormat::R8_Unorm;
        case GnPixelStorageMode::PSMZ32:
            if (m_32bitFloatZBufferFmt) {
                return GnDeviceFormat::D32_Float;
            }
        case GnPixelStorageMode::PSMZ24:
            if (m_24bitZBufferPackedFmt) {
                return GnDeviceFormat::D24_X8_Unorm;
            }
            else if (m_24bitZBuffer8bitStencilFmt) {
                return GnDeviceFormat::D24_S8_Unorm;
            }
            else {
                return GnDeviceFormat::D16_Unorm; // unfortunately
            }
        case GnPixelStorageMode::PSMZ16:
        case GnPixelStorageMode::PSMZ16S:
            return GnDeviceFormat::D16_Unorm;
    }

    return GnDeviceFormat::Unknown;
}

VkDevice GnDeviceVK::GetHandle() const
{
    return m_device;
}

VkCommandPool GnDeviceVK::GetDrawCommandPool() const
{
    return m_drawCmdPool;
}

VkCommandPool GnDeviceVK::GetTransferCommandPool() const
{
    return m_xferCmdPool;
}

void GnDeviceVK::InitFeatures()
{
    // GPU must support at least 24-bit depth buffer (Most GPUs supports 24-bit/32-bit depth buffer, this might be redundant)
    VkFormatProperties depthFmt{};

    // Checks 32-bit float depth buffer support...
    vkGetPhysicalDeviceFormatProperties(m_physicalDevice, VK_FORMAT_D32_SFLOAT, &depthFmt);

    if ((depthFmt.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
        m_32bitFloatZBufferFmt = true;
    }

    // Checks 24-bit depth & 8-bit stencil buffer support...
    vkGetPhysicalDeviceFormatProperties(m_physicalDevice, VK_FORMAT_D24_UNORM_S8_UINT, &depthFmt);

    if ((depthFmt.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
        m_24bitZBuffer8bitStencilFmt = true;
    }

    // Checks packed 24-bit depth buffer support...
    vkGetPhysicalDeviceFormatProperties(m_physicalDevice, VK_FORMAT_X8_D24_UNORM_PACK32, &depthFmt);

    if ((depthFmt.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
        m_24bitZBufferPackedFmt = true;
    }

    if (!(m_32bitFloatZBufferFmt || m_24bitZBuffer8bitStencilFmt || m_24bitZBufferPackedFmt)) {
        GnLog::Warn("GPU must support at least 24-bit depth buffer!");
    }

    VkPhysicalDeviceMemoryProperties memProperties{};

    vkGetPhysicalDeviceMemoryProperties(m_physicalDevice, &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        VkMemoryType& memType = memProperties.memoryTypes[i];

        if ((memType.propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) == VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) {
            m_supportedMemoryType |= GnMemoryType::DeviceLocal;
        }

        if ((memType.propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) == VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) {
            m_supportedMemoryType |= GnMemoryType::HostVisible;
        }

        if ((memType.propertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) == VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) {
            m_supportedMemoryType |= GnMemoryType::HostCoherent;
        }
    }
}

void GnDeviceVK::InitQueue()
{
    bool hasDirectQueue = false;
    uint32_t index = 0;
    std::vector<VkQueueFamilyProperties> queueFamilies;
    
    VulkanHelpers::GetDeviceQueueFamilies(m_physicalDevice, queueFamilies);
    
    for (auto& q : queueFamilies) {
        VkQueue cmdQueue;
        uint32_t currentIndex = index++;

        if ((q.queueFlags & GN_VK_DIRECT_COMMAND_QUEUE) == GN_VK_DIRECT_COMMAND_QUEUE) {
            vkGetDeviceQueue(m_device, currentIndex, 0, &cmdQueue);
            m_cmdQueues.insert({ GnCommandQueue::Direct, { currentIndex, cmdQueue } });
            hasDirectQueue = true;
        }
        else if ((q.queueFlags & VK_QUEUE_COMPUTE_BIT) == VK_QUEUE_COMPUTE_BIT) {
            vkGetDeviceQueue(m_device, currentIndex, 0, &cmdQueue);
            m_cmdQueues.insert({ GnCommandQueue::Compute, { currentIndex, cmdQueue } });
            m_asyncComputeSupport = true;
        }
        else if ((q.queueFlags & VK_QUEUE_TRANSFER_BIT) == VK_QUEUE_TRANSFER_BIT) {
            vkGetDeviceQueue(m_device, currentIndex, 0, &cmdQueue);
            m_cmdQueues.insert({ GnCommandQueue::Transfer, { currentIndex, cmdQueue } });
            m_asyncTransferSupport = true;
        }
    }

    if (!hasDirectQueue) {
        GnLog::Critical("No direct queue family found!");
        assert(0);
    }
}

void GnDeviceVK::InitCommandPools()
{
    VkCommandPoolCreateInfo cmdPoolInfo{};

    cmdPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    cmdPoolInfo.queueFamilyIndex = m_cmdQueues[GnCommandQueue::Direct].queueFamilyIndex;

    if (VK_CHECK(vkCreateCommandPool(m_device, &cmdPoolInfo, nullptr, &m_drawCmdPool))) {
        GnLog::Critical("Cannot create command pool!");
        assert(0);
    }

    // No async queue for now...
    if (VK_CHECK(vkCreateCommandPool(m_device, &cmdPoolInfo, nullptr, &m_xferCmdPool))) {
        GnLog::Critical("Cannot create command pool!");
        assert(0);
    }
}

VkSurfaceKHR GnDeviceVK::CreateSurface(const GnSwapchainDesc& desc)
{
    VkSurfaceKHR surface = VK_NULL_HANDLE;

#ifdef _WIN32
    VkWin32SurfaceCreateInfoKHR surfaceInfo{};
    surfaceInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    surfaceInfo.hinstance = GetModuleHandle(nullptr);
    surfaceInfo.hwnd = static_cast<HWND>(desc.window->GetNativeHandle());

    if (VK_CHECK(vkCreateWin32SurfaceKHR(m_instance, &surfaceInfo, nullptr, &surface))) {
        GnLog::Critical("Cannot create surface");
        return VK_NULL_HANDLE;
    }
#endif

    return surface;
}
