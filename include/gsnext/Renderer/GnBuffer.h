#pragma once

class GnBuffer
{
public:
    virtual ~GnBuffer() { }

    virtual void Map() = 0;
    virtual void Unmap() = 0;

protected:
    GnBuffer() { }
};
