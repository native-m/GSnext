#pragma once

class GnDeviceMemory
{
public:
    virtual ~GnDeviceMemory() { }

    virtual void Map() const = 0;
    virtual void Unmap() const = 0;
    virtual size_t GetSize() const = 0;

protected:
    GnDeviceMemory() { }
};
