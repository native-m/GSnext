#pragma once

#include "GnRegisters.h"

class GnPacketBuffer
{
public:
    GnPacketBuffer();
    ~GnPacketBuffer();

    // Unpacked mode
    void SetPRIM(const GnReg64& r);
    void SetRGBAQ(const GnReg64& r);
    void SetST(const GnReg64& r);
    void SetUV(const GnReg64& r);
    void SetXYZF2(const GnReg64& r);
    void SetXYZ2(const GnReg64& r);

    // Packed mode
    void SetPRIM(const GnReg128& r);
    void SetRGBA(const GnReg128& r);
    void SetSTQ(const GnReg128& r);
    void SetUV(const GnReg128& r);
    void SetXYZF2(const GnReg128& r);
    void SetXYZ2(const GnReg128& r);
};
