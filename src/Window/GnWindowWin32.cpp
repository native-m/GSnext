#include "GnWindowWin32.h"
#include <gsnext/GnLog.h>
#include <locale>
#include <codecvt>

GnWindowWin32::GnWindowWin32() :
    m_hWnd(nullptr)
{
}

GnWindowWin32::~GnWindowWin32()
{
    Detach();
}

void GnWindowWin32::Attach(void* handle)
{
}

void GnWindowWin32::Detach()
{
    if (m_hWnd != nullptr) {
        DestroyWindow(m_hWnd);
    }

    m_hWnd = nullptr;
}

bool GnWindowWin32::Initialize(const std::string& name, int w, int h)
{
    HINSTANCE hInstance = GetModuleHandle(nullptr);
    WNDCLASSEX wc{};
    std::wstring str = std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().from_bytes(name);

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = L"GSnextWnd";
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    RegisterClassEx(&wc);

    m_hWnd = CreateWindowEx(
        0,
        wc.lpszClassName,
        str.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        w, h,
        nullptr, nullptr,
        hInstance, this);

    if (m_hWnd == nullptr) {
        GnLog::Error("Cannot create window (error code: {:x})", GetLastError());
        return false;
    }

    // Adjust client size
    RECT wndRect{};

    GetWindowRect(m_hWnd, &wndRect);
    AdjustWindowRect(&wndRect, WS_OVERLAPPEDWINDOW, FALSE);
    SetWindowPos(
        m_hWnd,
        nullptr,
        wndRect.left,
        wndRect.top,
        wndRect.right - wndRect.left,
        wndRect.bottom - wndRect.top,
        0);

    return true;
}

void GnWindowWin32::Open()
{
    ShowWindow(m_hWnd, SW_SHOW);
    SetForegroundWindow(m_hWnd);
    UpdateWindow(m_hWnd);
    m_isOpen = true;
}

void GnWindowWin32::Close()
{
    ShowWindow(m_hWnd, SW_HIDE);
    m_isOpen = false;
}

bool GnWindowWin32::ProcessMessage()
{
    MSG msg{};

    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if (msg.message == WM_QUIT) {
        return false;
    }

    return true;
}

void GnWindowWin32::GetSize(GnSize2D& size)
{
    RECT rect;

    GetClientRect(m_hWnd, &rect);

    size.width = rect.right - rect.left;
    size.height = rect.bottom - rect.top;
}

void* GnWindowWin32::GetNativeHandle()
{
    return static_cast<HWND>(m_hWnd);
}

bool GnWindowWin32::IsOpen()
{
    return m_isOpen;
}

LRESULT GnWindowWin32::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    GnWindowWin32* wnd;

    if (uMsg == WM_NCCREATE) {
        LPCREATESTRUCT wndCreate = reinterpret_cast<LPCREATESTRUCT>(lParam);
        wnd = reinterpret_cast<GnWindowWin32*>(wndCreate->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(wnd));
        wnd->m_hWnd = hwnd;
    }
    else {
        wnd = reinterpret_cast<GnWindowWin32*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    if (wnd == nullptr) {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return wnd->OnMessage(uMsg, wParam, lParam);
}

LRESULT GnWindowWin32::OnMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        Close();
        break;
    case WM_DESTROY:
        // PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
    }

    return 0;
}
