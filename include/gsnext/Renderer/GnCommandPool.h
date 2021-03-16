#pragma once

class GnCommandPool
{
public:
    virtual ~GnCommandPool() { }

    virtual void Reset() = 0;

protected:
    GnCommandPool() { }
};
