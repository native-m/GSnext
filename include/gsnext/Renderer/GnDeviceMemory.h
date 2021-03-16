#pragma once

class GnDeviceMemory
{
public:
    virtual ~GnDeviceMemory() { }

    virtual size_t GetSize() = 0;

private:
    GnDeviceMemory() { }
};
