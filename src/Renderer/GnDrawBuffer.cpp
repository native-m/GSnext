#include <gsnext/Renderer/GnDrawBuffer.h>

#define GN_VTX_KICK_ADC 0x01
#define GN_VTX_KICK_FOG 0x02

GnDrawBuffer::~GnDrawBuffer()
{
}

void GnDrawBuffer::SetPRIM(const GnReg64& r)
{
    m_state.PRIM.r64.u32[0] = r.u32[0];
}

void GnDrawBuffer::SetRGBAQ(const GnReg64& r)
{
    m_state.RGBAQ.r64 = r;
}

void GnDrawBuffer::SetST(const GnReg64& r)
{
    m_state.ST.r64 = r;
}

void GnDrawBuffer::SetUV(const GnReg64& r)
{
    m_state.UV.r64 = r;
}

void GnDrawBuffer::SetXYZF2(const GnReg64& r)
{
    m_state.XYZF2.r64 = r;
    VertexKick(false, true); // Vertex kick (adc = 0)
}

void GnDrawBuffer::SetXYZ2(const GnReg64& r)
{
    m_state.XYZ2.r64 = r;
    VertexKick(false, false); // Vertex kick (adc = 0)
}

void GnDrawBuffer::SetTEX0_1(const GnReg64& r)
{
    m_state.drawEnv[0].TEX0.r64 = r;
}

void GnDrawBuffer::SetTEX0_2(const GnReg64& r)
{
    m_state.drawEnv[1].TEX0.r64 = r;
}

void GnDrawBuffer::SetCLAMP_1(const GnReg64& r)
{
    m_state.drawEnv[0].CLAMP.r64 = r;
}

void GnDrawBuffer::SetCLAMP_2(const GnReg64& r)
{
    m_state.drawEnv[1].CLAMP.r64 = r;
}

void GnDrawBuffer::SetFOG(const GnReg64& r)
{
    m_state.FOG.r64 = r;
}

void GnDrawBuffer::SetXYZF3(const GnReg64& r)
{
    m_state.XYZF3.r64 = r;
    VertexKick(true, true); // Vertex kick (adc = 1)
}

void GnDrawBuffer::SetXYZ3(const GnReg64& r)
{
    m_state.XYZ3.r64 = r;
    VertexKick(true, false); // Vertex kick (adc = 1)
}

void GnDrawBuffer::SetNOP(const GnReg64& r)
{
    // nope :)
}

void GnDrawBuffer::SetTEX1_1(const GnReg64& r)
{
    m_state.drawEnv[0].TEX1.r64 = r;
}

void GnDrawBuffer::SetTEX1_2(const GnReg64& r)
{
    m_state.drawEnv[1].TEX1.r64 = r;
}

void GnDrawBuffer::SetTEX2_1(const GnReg64& r)
{
    m_state.drawEnv[0].TEX2.r64 = r;
}

void GnDrawBuffer::SetTEX2_2(const GnReg64& r)
{
    m_state.drawEnv[1].TEX2.r64 = r;
}

void GnDrawBuffer::SetXYOFFSET_1(const GnReg64& r)
{
}

void GnDrawBuffer::SetXYOFFSET_2(const GnReg64& r)
{
}

void GnDrawBuffer::SetPRMODECONT(const GnReg64& r)
{
}

void GnDrawBuffer::SetPRMODE(const GnReg64& r)
{
}

void GnDrawBuffer::SetTEXCLUT(const GnReg64& r)
{
}

void GnDrawBuffer::SetSCANMSK(const GnReg64& r)
{
}

void GnDrawBuffer::SetMIPTBP1_1(const GnReg64& r)
{
}

void GnDrawBuffer::SetMIPTBP1_2(const GnReg64& r)
{
}

void GnDrawBuffer::SetMIPTBP2_1(const GnReg64& r)
{
}

void GnDrawBuffer::SetMIPTBP2_2(const GnReg64& r)
{
}

void GnDrawBuffer::SetTEXA(const GnReg64& r)
{
}

void GnDrawBuffer::SetFOGCOL(const GnReg64& r)
{
}

void GnDrawBuffer::SetTEXFLUSH(const GnReg64& r)
{
}

void GnDrawBuffer::SetSCISSOR_1(const GnReg64& r)
{
}

void GnDrawBuffer::SetSCISSOR_2(const GnReg64& r)
{
}

void GnDrawBuffer::SetALPHA_1(const GnReg64& r)
{
}

void GnDrawBuffer::SetALPHA_2(const GnReg64& r)
{
}

void GnDrawBuffer::SetDIMX(const GnReg64& r)
{
}

void GnDrawBuffer::SetDTHE(const GnReg64& r)
{
}

void GnDrawBuffer::SetCOLCLAMP(const GnReg64& r)
{
}

void GnDrawBuffer::SetTEST_1(const GnReg64& r)
{
}

void GnDrawBuffer::SetTEST_2(const GnReg64& r)
{
}

void GnDrawBuffer::SetPABE(const GnReg64& r)
{
}

void GnDrawBuffer::SetFBA_1(const GnReg64& r)
{
}

void GnDrawBuffer::SetFBA_2(const GnReg64& r)
{
}

void GnDrawBuffer::SetFRAME_1(const GnReg64& r)
{
}

void GnDrawBuffer::SetFRAME_2(const GnReg64& r)
{
}

void GnDrawBuffer::SetZBUF_1(const GnReg64& r)
{
}

void GnDrawBuffer::SetZBUF_2(const GnReg64& r)
{
}

void GnDrawBuffer::SetSTRGBAQXYZF2(const GnReg64* regList)
{
    m_state.ST.r64 = regList[0];
    m_state.RGBAQ.r64 = regList[1];
    m_state.XYZF2.r64 = regList[2];
    VertexKick(false, true);
}

void GnDrawBuffer::SetSTRGBAQXYZ2(const GnReg64* regList)
{
    m_state.ST.r64 = regList[0];
    m_state.RGBAQ.r64 = regList[1];
    m_state.XYZ2.r64 = regList[2];
    VertexKick(false, true);
}

void GnDrawBuffer::SetPRIM(const GnReg128& r)
{
    m_state.PRIM.r64.u32[0] = r.u32[0] & 0x7ff;
}

void GnDrawBuffer::SetRGBA(const GnReg128& r)
{
    m_state.RGBAQ.r64.u32[0] = (r.u32[3] << 24) | (r.u32[2] << 16) | (r.u32[1] << 8) | r.u32[0];
}

void GnDrawBuffer::SetSTQ(const GnReg128& r)
{
    m_state.ST.r64.f32[0] = r.f32[0];
    m_state.ST.r64.f32[1] = r.f32[1];
    m_state.RGBAQ.r64.f32[1] = r.f32[2];
}

void GnDrawBuffer::SetUV(const GnReg128& r)
{
    m_state.UV.r64.u32[0] = ((r.u32[1] & 0x3FFF) << 16) | (r.u32[0] & 0x3FFF);
}

void GnDrawBuffer::SetXYZF2(const GnReg128& r)
{
    m_state.XYZF2.r64.u32[0] = ((r.u32[1] & 0xFFFF) << 16) | (r.u32[0] & 0xFFFF);
    m_state.XYZF2.r64.u32[1] = ((r.u32[3] & 0x0FF0) << 12) | ((r.u32[2] & 0x0FFFFFF0) >> 4);
    VertexKick(false, true);
}

void GnDrawBuffer::SetXYZ2(const GnReg128& r)
{
    m_state.XYZ2.r64.u32[0] = ((r.u32[1] & 0xFFFF) << 16) | (r.u32[0] & 0xFFFF);
    m_state.XYZ2.r64.u32[1] = r.u32[2];
    VertexKick(false, false);
}

void GnDrawBuffer::SetFOG(const GnReg128& r)
{
}

void GnDrawBuffer::SetA_D(const GnReg128& r)
{
    uint32_t reg = r.u32[2] & 0xFF;
}

void GnDrawBuffer::SetNOP(const GnReg128& r)
{
}

void GnDrawBuffer::SetSTQRGBAXYZF2(const GnReg128* regList)
{
    m_state.ST.r64.f32[0] = regList[0].f32[0];
    m_state.ST.r64.f32[1] = regList[0].f32[1];
    m_state.RGBAQ.r64.u32[0] = (regList[1].u32[3] << 24)| (regList[1].u32[2] << 16) | (regList[1].u32[1] << 8) | regList[1].u32[0];
    m_state.RGBAQ.r64.f32[1] = regList[0].f32[2];
    m_state.XYZF2.r64.u32[0] = ((regList[2].u32[1] & 0xFFFF) << 16) | (regList[2].u32[0] & 0xFFFF);
    m_state.XYZF2.r64.u32[1] = ((regList[2].u32[3] & 0x0FF0) << 12) | ((regList[2].u32[2] & 0x0FFFFFF0) >> 4);
    VertexKick(false, true);
}

void GnDrawBuffer::SetSTQRGBAXYZ2(const GnReg128* regList)
{
    m_state.ST.r64.f32[0] = regList[0].f32[0];
    m_state.ST.r64.f32[1] = regList[0].f32[1];
    m_state.RGBAQ.r64.u32[0] = (regList[1].u32[3] << 24) | (regList[1].u32[2] << 16) | (regList[1].u32[1] << 8) | regList[1].u32[0];
    m_state.RGBAQ.r64.f32[1] = regList[0].f32[2];
    m_state.XYZ2.r64.u32[0] = ((regList[2].u32[1] & 0xFFFF) << 16) | (regList[2].u32[0] & 0xFFFF);
    m_state.XYZ2.r64.u32[1] = regList[2].u32[2];
    VertexKick(false, false);
}


void GnDrawBuffer::VertexKick(bool adc, bool withFog)
{
}

GnDrawBuffer::GnDrawBuffer()
{
}

const GnDrawBuffer::GIFRegHandler GnDrawBuffer::g_gifRegHandler[256] = {
    /* 0x00 */ &GnDrawBuffer::SetPRIM,
    /* 0x01 */ &GnDrawBuffer::SetRGBAQ,
    /* 0x02 */ &GnDrawBuffer::SetST,
    /* 0x03 */ &GnDrawBuffer::SetUV,
    /* 0x04 */ &GnDrawBuffer::SetXYZF2,
    /* 0x05 */ &GnDrawBuffer::SetXYZ2,
    /* 0x06 */ &GnDrawBuffer::SetTEX0_1,
    /* 0x07 */ &GnDrawBuffer::SetTEX0_2,
    /* 0x08 */ &GnDrawBuffer::SetCLAMP_1,
    /* 0x09 */ &GnDrawBuffer::SetCLAMP_2,
    /* 0x0a */ &GnDrawBuffer::SetFOG,
    /* 0x0b */ nullptr,
    /* 0x0c */ &GnDrawBuffer::SetXYZF3,
    /* 0x0d */ &GnDrawBuffer::SetXYZ3,
    /* 0x0e */ nullptr,
    /* 0x0f */ nullptr,
    /* 0x10 */ nullptr,
    /* 0x11 */ nullptr,
    /* 0x12 */ nullptr,
    /* 0x13 */ nullptr,
    /* 0x14 */ &GnDrawBuffer::SetTEX1_1,
    /* 0x15 */ &GnDrawBuffer::SetTEX1_2,
    /* 0x16 */ &GnDrawBuffer::SetTEX2_1,
    /* 0x17 */ &GnDrawBuffer::SetTEX2_2,
    /* 0x18 */ &GnDrawBuffer::SetXYOFFSET_1,
    /* 0x19 */ &GnDrawBuffer::SetXYOFFSET_2,
    /* 0x1a */ &GnDrawBuffer::SetPRMODECONT,
    /* 0x1b */ &GnDrawBuffer::SetPRMODE,
    /* 0x1c */ &GnDrawBuffer::SetTEXCLUT,
    /* 0x1d */ nullptr,
    /* 0x1e */ nullptr,
    /* 0x1f */ nullptr,
    /* 0x20 */ nullptr,
    /* 0x21 */ nullptr,
    /* 0x22 */ &GnDrawBuffer::SetSCANMSK,
    /* 0x23 */ nullptr,
    /* 0x24 */ nullptr,
    /* 0x25 */ nullptr,
    /* 0x26 */ nullptr,
    /* 0x27 */ nullptr,
    /* 0x28 */ nullptr,
    /* 0x29 */ nullptr,
    /* 0x2a */ nullptr,
    /* 0x2b */ nullptr,
    /* 0x2c */ nullptr,
    /* 0x2d */ nullptr,
    /* 0x2e */ nullptr,
    /* 0x2f */ nullptr,
    /* 0x30 */ nullptr,
    /* 0x31 */ nullptr,
    /* 0x32 */ nullptr,
    /* 0x33 */ nullptr,
    /* 0x34 */ &GnDrawBuffer::SetMIPTBP1_1,
    /* 0x35 */ &GnDrawBuffer::SetMIPTBP1_2,
    /* 0x36 */ &GnDrawBuffer::SetMIPTBP2_1,
    /* 0x37 */ &GnDrawBuffer::SetMIPTBP2_2,
    /* 0x38 */ nullptr,
    /* 0x39 */ nullptr,
    /* 0x3a */ nullptr,
    /* 0x3b */ &GnDrawBuffer::SetTEXA,
    /* 0x3c */ nullptr,
    /* 0x3d */ &GnDrawBuffer::SetFOGCOL,
    /* 0x3e */ nullptr,
    /* 0x3f */ &GnDrawBuffer::SetTEXFLUSH,
    /* 0x40 */ &GnDrawBuffer::SetSCISSOR_1,
    /* 0x41 */ &GnDrawBuffer::SetSCISSOR_2,
    /* 0x42 */ &GnDrawBuffer::SetALPHA_1,
    /* 0x43 */ &GnDrawBuffer::SetALPHA_2,
    /* 0x44 */ &GnDrawBuffer::SetDIMX,
    /* 0x45 */ &GnDrawBuffer::SetDTHE,
    /* 0x46 */ &GnDrawBuffer::SetCOLCLAMP,
    /* 0x47 */ &GnDrawBuffer::SetTEST_1,
    /* 0x48 */ &GnDrawBuffer::SetTEST_2,
    /* 0x49 */ &GnDrawBuffer::SetPABE,
    /* 0x4a */ &GnDrawBuffer::SetFBA_1,
    /* 0x4b */ &GnDrawBuffer::SetFBA_2,
    /* 0x4c */ &GnDrawBuffer::SetFRAME_1,
    /* 0x4d */ &GnDrawBuffer::SetFRAME_2,
    /* 0x4e */ &GnDrawBuffer::SetZBUF_1,
    /* 0x4f */ &GnDrawBuffer::SetZBUF_2
};
