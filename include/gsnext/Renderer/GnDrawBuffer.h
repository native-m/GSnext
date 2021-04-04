#pragma once

#include <gsnext/GnRegisters.h>

class GnDrawBuffer
{
public:
    typedef void (GnDrawBuffer::*GIFRegHandler)(const GnReg64& r);

    virtual ~GnDrawBuffer();

    virtual void Begin() = 0;

    // Unpacked mode
    void SetPRIM(const GnReg64& r);
    void SetRGBAQ(const GnReg64& r);
    void SetST(const GnReg64& r);
    void SetUV(const GnReg64& r);
    void SetXYZF2(const GnReg64& r);
    void SetXYZ2(const GnReg64& r);
    void SetTEX0_1(const GnReg64& r);
    void SetTEX0_2(const GnReg64& r);
    void SetCLAMP_1(const GnReg64& r);
    void SetCLAMP_2(const GnReg64& r);
    void SetFOG(const GnReg64& r);
    void SetXYZF3(const GnReg64& r);
    void SetXYZ3(const GnReg64& r);
    void SetNOP(const GnReg64& r);
    void SetTEX1_1(const GnReg64& r);
    void SetTEX1_2(const GnReg64& r);
    void SetTEX2_1(const GnReg64& r);
    void SetTEX2_2(const GnReg64& r);
    void SetXYOFFSET_1(const GnReg64& r);
    void SetXYOFFSET_2(const GnReg64& r);
    void SetPRMODECONT(const GnReg64& r);
    void SetPRMODE(const GnReg64& r);
    void SetTEXCLUT(const GnReg64& r);
    void SetSCANMSK(const GnReg64& r);
    void SetMIPTBP1_1(const GnReg64& r);
    void SetMIPTBP1_2(const GnReg64& r);
    void SetMIPTBP2_1(const GnReg64& r);
    void SetMIPTBP2_2(const GnReg64& r);
    void SetTEXA(const GnReg64& r);
    void SetFOGCOL(const GnReg64& r);
    void SetTEXFLUSH(const GnReg64& r);
    void SetSCISSOR_1(const GnReg64& r);
    void SetSCISSOR_2(const GnReg64& r);
    void SetALPHA_1(const GnReg64& r);
    void SetALPHA_2(const GnReg64& r);
    void SetDIMX(const GnReg64& r);
    void SetDTHE(const GnReg64& r);
    void SetCOLCLAMP(const GnReg64& r);
    void SetTEST_1(const GnReg64& r);
    void SetTEST_2(const GnReg64& r);
    void SetPABE(const GnReg64& r);
    void SetFBA_1(const GnReg64& r);
    void SetFBA_2(const GnReg64& r);
    void SetFRAME_1(const GnReg64& r);
    void SetFRAME_2(const GnReg64& r);
    void SetZBUF_1(const GnReg64& r);
    void SetZBUF_2(const GnReg64& r);

    // Commonly used REGLIST register set
    void SetSTRGBAQXYZF2(const GnReg64* regList);
    void SetSTRGBAQXYZ2(const GnReg64* regList);

    // Packed mode
    void SetPRIM(const GnReg128& r);
    void SetRGBA(const GnReg128& r);
    void SetSTQ(const GnReg128& r);
    void SetUV(const GnReg128& r);
    void SetXYZF2(const GnReg128& r);
    void SetXYZ2(const GnReg128& r);
    void SetFOG(const GnReg128& r);
    void SetA_D(const GnReg128& r);
    void SetNOP(const GnReg128& r);

    // Commonly used PACKED register set
    void SetSTQRGBAXYZF2(const GnReg128* regList);
    void SetSTQRGBAXYZ2(const GnReg128* regList);

    virtual void End() = 0;
    virtual void Flush() = 0;

    void VertexKick(bool adc, bool withFog);

private:
    GnRegState m_state;

    static const GIFRegHandler g_gifRegHandler[256];

protected:
    GnDrawBuffer();
};
