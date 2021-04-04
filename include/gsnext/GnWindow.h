#pragma once

#include <memory>
#include <string>

class GnWindow
{
public:
    virtual ~GnWindow() { }

    virtual void Attach(void* handle) { }
    virtual void Detach() { }
    virtual bool Initialize(const std::string& name, int w, int h) { return false; }
    virtual void Open() { }
    virtual void Close() { }
    virtual bool ProcessMessage() { return true; }
    virtual void* GetNativeHandle() = 0;
    virtual bool IsOpen() { return true; }

    static std::shared_ptr<GnWindow> Create();
    static std::shared_ptr<GnWindow> CreateManaged();

protected:
    GnWindow() { }
};
