#pragma once

#include <gsnext/GnWindow.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

class GnManagedWindowWin32 : public GnWindow
{
public:
    GnManagedWindowWin32();
    virtual ~GnManagedWindowWin32();

    void Attach(void* handle) override;
    void Detach() override;
    void* GetNativeHandle() override;

private:
    HWND m_hWnd;
};
