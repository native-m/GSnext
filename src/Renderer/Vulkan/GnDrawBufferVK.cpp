#include "GnDrawBufferVK.h"
#include "GnDeviceVK.h"

#include <gsnext/GnLog.h>

GnDrawBufferVK::GnDrawBufferVK(GnDeviceVK* parentDevice) :
    m_parentDevice(parentDevice)
{
    Init();
}

GnDrawBufferVK::~GnDrawBufferVK()
{
}

void GnDrawBufferVK::Begin()
{
    VkCommandBufferBeginInfo cmdBegin{};

    cmdBegin.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    cmdBegin.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    if (VK_CHECK(vkBeginCommandBuffer(m_drawCmdBuffer, &cmdBegin))) {
        GnLog::Error("Failed to begin command buffer recording");
        assert(0);
    }
}

void GnDrawBufferVK::End()
{
    if (VK_CHECK(vkEndCommandBuffer(m_drawCmdBuffer))) {
        GnLog::Error("Failed to end command buffer recording");
        assert(0);
    }
}

void GnDrawBufferVK::Flush()
{
}

void GnDrawBufferVK::Init()
{
}
