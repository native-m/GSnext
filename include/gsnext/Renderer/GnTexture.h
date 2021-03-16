#pragma once

class GnTexture
{
public:
    virtual ~GnTexture() { }

    virtual size_t Map() = 0;
    virtual size_t Unmap() = 0;

protected:
    GnTexture() { }
};
