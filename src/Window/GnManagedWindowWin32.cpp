#include "GnManagedWindowWin32.h"
#include <gsnext/GnLog.h>

GnManagedWindowWin32::GnManagedWindowWin32() :
    m_hWnd(nullptr)
{
}

GnManagedWindowWin32::~GnManagedWindowWin32()
{
}

void GnManagedWindowWin32::Attach(void* handle)
{
    if (!IsWindow(static_cast<HWND>(handle))) {
        GnLog::Critical("Invalid HWND!");
        assert(0);
    }

    m_hWnd = static_cast<HWND>(handle);
}

void GnManagedWindowWin32::Detach()
{
}

void* GnManagedWindowWin32::GetNativeHandle()
{
    return m_hWnd;
}
