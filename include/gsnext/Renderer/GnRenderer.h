#pragma once

#include <gsnext/Renderer/GnDevice.h>

class GnRenderer
{
public:
    virtual ~GnRenderer();

    virtual void GetAvailableAdapters(std::vector<GnAdapterInfo>& adapterInfos) = 0;
    virtual bool OpenDevice(GnAdapterId id);
    virtual void CloseDevice();

    uint32_t HandlePacked();
    uint32_t HandleReglist();
    uint32_t HandleImage();

    static std::shared_ptr<GnRenderer> Create(GnBackendRenderer backend);

protected:
    std::shared_ptr<GnDevice> m_device;

    GnRenderer();
};
