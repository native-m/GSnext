#pragma once

#include <gsnext/GnWindow.h>
#include <gsnext/Renderer/GnDevice.h>

class GnRenderer
{
public:
    virtual ~GnRenderer();

    bool Open(std::shared_ptr<GnWindow>& window, const GnAdapterId& id);
    void Close();
    void Vsync();

    virtual void GetAvailableAdapters(std::vector<GnAdapterInfo>& adapterInfos) = 0;
    virtual bool OpenDevice(const GnAdapterId& id) = 0;
    virtual void Test() = 0;
    virtual void Render() = 0;
    virtual void CloseDevice() = 0;

    uint32_t HandlePacked();
    uint32_t HandleReglist();
    uint32_t HandleImage();

    static std::shared_ptr<GnRenderer> Create(GnBackendRenderer backend);

protected:
    std::shared_ptr<GnDevice> m_device;
    GnSwapchain* m_outputWindowSwapchain;

    GnRenderer();
};
