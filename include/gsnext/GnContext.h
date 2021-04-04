#pragma once

#include <gsnext/GnConfig.h>
#include <gsnext/GnWindow.h>
#include <gsnext/Renderer/GnDevice.h>
#include <atomic>

class GnContext {
public:
    GnContext();
    ~GnContext();

    bool Open(void** pDsp, const char* title);
    void Close();
    void OpenConfigWindow();
    void CloseConfigWindow();

    template<uint32_t i>
    void Transfer(const uint32_t* mem, uint32_t size);
    void Vsync();

    void SetRegsMem(uint32_t* addr);
    void SetIniPath(const std::string& path);

    std::shared_ptr<GnDevice>& GetDevice();

private:
    std::shared_ptr<GnWindow> m_window;
    std::shared_ptr<GnDevice> m_device;
    std::string m_iniPath;
    GnConfig m_config;

    std::atomic<bool> m_configWindowOpened = false;

    bool InitDevice();
    void InitSwapchain();

    void LoadConfig();
    void SaveConfig();
    void ConfigWindowThread();
};
