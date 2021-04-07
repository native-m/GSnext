#pragma once

#include <gsnext/GnWindow.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

class GnWindowWin32 : public GnWindow
{
public:
    GnWindowWin32();
    virtual ~GnWindowWin32();

    void Attach(void* handle) override;
    void Detach() override;
    bool Initialize(const std::string& name, int w, int h) override;
    void Open() override;
    void Close() override;
    bool ProcessMessage() override;
    void GetSize(GnSize2D& size) override;
    void* GetNativeHandle() override;
    bool IsOpen() override;

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
    HWND m_hWnd;
    bool m_isOpen;

    LRESULT OnMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};
