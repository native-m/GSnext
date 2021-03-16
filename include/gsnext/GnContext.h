#pragma once

#include "GnWindow.h"

class GnContext {
public:
    ~GnContext();

    bool Initialize(std::shared_ptr<GnWindow>& window);
    void OpenConfigWindow();

    template<uint32_t i>
    void Transfer(const uint32_t* mem, uint32_t size);
    void Vsync();
    void ResetDevice();

private:
    std::shared_ptr<GnWindow> m_window;
};
