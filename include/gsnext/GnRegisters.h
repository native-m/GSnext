#pragma once

#include <cstdint>
#include <xmmintrin.h>
#include <gsnext/GnCommon.h>

enum class GnGifReg
{
    PRIM = 0x00,
    RGBAQ = 0x01,
    ST = 0x02,
    UV = 0x03,
    XYZF2 = 0x04,
    XYZ2 = 0x05,
    TEX0_1 = 0x06,
    TEX0_2 = 0x07,
    CLAMP_1 = 0x08,
    CLAMP_2 = 0x09,
    FOG = 0x0a,
    XYZF3 = 0x0c,
    XYZ3 = 0x0d,
    A_D = 0x0e,
    NOP = 0x0f,
    TEX1_1 = 0x14,
    TEX1_2 = 0x15,
    TEX2_1 = 0x16,
    TEX2_2 = 0x17,
    XYOFFSET_1 = 0x18,
    XYOFFSET_2 = 0x19,
    PRMODECONT = 0x1a,
    PRMODE = 0x1b,
    TEXCLUT = 0x1c,
    SCANMSK = 0x22,
    MIPTBP1_1 = 0x34,
    MIPTBP1_2 = 0x35,
    MIPTBP2_1 = 0x36,
    MIPTBP2_2 = 0x37,
    TEXA = 0x3b,
    FOGCOL = 0x3d,
    TEXFLUSH = 0x3f,
    SCISSOR_1 = 0x40,
    SCISSOR_2 = 0x41,
    ALPHA_1 = 0x42,
    ALPHA_2 = 0x43,
    DIMX = 0x44,
    DTHE = 0x45,
    COLCLAMP = 0x46,
    TEST_1 = 0x47,
    TEST_2 = 0x48,
    PABE = 0x49,
    FBA_1 = 0x4a,
    FBA_2 = 0x4b,
    FRAME_1 = 0x4c,
    FRAME_2 = 0x4d,
    ZBUF_1 = 0x4e,
    ZBUF_2 = 0x4f,
    BITBLTBUF = 0x50,
    TRXPOS = 0x51,
    TRXREG = 0x52,
    TRXDIR = 0x53,
    HWREG = 0x54,
    SIGNAL = 0x60,
    FINISH = 0x61,
    LABEL = 0x62,
};

#pragma pack(push, 1)

// All GIF registers must equal to 8 bytes!

// ----- Drawing environment regs ----- //

// Frame buffer setting regsiter
struct GnRegFRAME
{
    uint16_t FBP : 9;
    uint8_t _PAD0 : 7;
    uint8_t FBW : 6;
    uint8_t _PAD1 : 2;
    uint8_t PSM : 6;
    uint32_t FBMSK;
};

// Z-buffer/Depth buffer register
struct GnRegZBUF
{
    uint16_t ZBP : 9;
    uint16_t _PAD0 : 15;
    uint8_t PSM : 4;
    uint8_t ZMSK : 1;
    uint32_t _PAD1 : 31;
};

// Texture info register
struct GnRegTEX0
{
    uint16_t TBP0 : 14;
    uint8_t TBW : 6;
    uint8_t PSM : 6;
    uint8_t TW : 4;
    uint8_t TH : 4;
    uint8_t TCC : 1;
    uint8_t TFX : 2;
    uint16_t CBP : 14;
    uint8_t CPSM : 4;
    uint8_t CSM : 1;
    uint8_t CSA : 5;
    uint8_t CLD : 3;
};

// Texture sampler info register
struct GnRegTEX1
{
    uint8_t LCM : 1;
    uint8_t _PAD1 : 1;
    uint8_t MXL : 3;
    uint8_t MMAG : 1;
    uint8_t MMIN : 3;
    uint8_t MTBA : 1;
    uint16_t _PAD2 : 9;
    uint8_t L : 2;
    uint16_t _PAD3 : 11;
    int16_t K : 12;
    uint32_t _PAD4 : 20;
};

// Subset of TEX0 register
struct GnRegTEX2
{
    uint32_t _PAD0 : 20;
    uint8_t PSM : 6;
    uint16_t _PAD1 : 11;
    uint16_t CBP : 14;
    uint8_t CPSM : 4;
    uint8_t CSM : 1;
    uint8_t CSA : 5;
    uint8_t CLD : 3;
};

// Texture mipmap setting regsiter (Level 1-3)
struct GnRegMIPTBP1
{
    uint16_t TBP1 : 14;
    uint8_t TBW1 : 6;
    uint16_t TBP2 : 14;
    uint8_t TBW2 : 6;
    uint16_t TBP3 : 14;
    uint8_t TBW3 : 6;
    uint8_t _PAD0 : 4;
};

// Texture mipmap setting regsiter (Level 4-6)
struct GnRegMIPTBP2
{
    uint16_t TBP4 : 14;
    uint8_t TBW4 : 6;
    uint16_t TBP5 : 14;
    uint8_t TBW5 : 6;
    uint16_t TBP6 : 14;
    uint8_t TBW6 : 6;
    uint8_t _PAD0 : 4;
};

// Texture wrap setting register
struct GnRegCLAMP
{
    uint8_t WMS : 2;
    uint8_t WMT : 2;
    uint16_t MINU : 10;
    uint16_t MAXU : 10;
    uint16_t MINV : 10;
    uint16_t MAXV : 10;
    uint32_t _PAD0 : 20;
};

// Pixel test control register
struct GnRegTEST
{
    uint8_t ATE : 1;
    uint8_t ATST : 3;
    uint8_t AREF : 8;
    uint8_t AFAIL : 2;
    uint8_t DATE : 1;
    uint8_t DATM : 1;
    uint8_t ZTE : 1;
    uint8_t ZTST : 2;
    uint64_t _PAD0 : 45;
};

// Alpha blending setting register
struct GnRegALPHA
{
    uint8_t A : 2;
    uint8_t B : 2;
    uint8_t C : 2;
    uint8_t D : 2;
    uint8_t _PAD0[3];
    uint8_t FIX;
    uint8_t _PAD1[3];
};

// Offset value setting register (Drawing offset)
struct GnRegXYOFFSET
{
    uint16_t OFX;
    uint16_t _PAD0;
    uint16_t OFY;
    uint16_t _PAD1;
};

// Scissoring area setting register
struct GnRegSCISSOR
{
    uint16_t SCAX0 : 11;
    uint8_t _PAD0 : 5;
    uint16_t SCAX1 : 11;
    uint8_t _PAD1 : 5;
    uint16_t SCAY0 : 11;
    uint8_t _PAD2 : 5;
    uint16_t SCAY1 : 11;
    uint8_t _PAD3 : 5;
};

// Alpha correction value register
struct GnRegFBA
{
    uint8_t FBA : 1;
    uint32_t _PAD0 : 24;
    uint32_t _PAD1;
};

// ----- Drawing function regs ----- //

// Drawing primitive setting register
struct GnRegPRIM
{
    uint8_t PRIM : 3;
    uint8_t IIP : 1;
    uint8_t TME : 1;
    uint8_t FGE : 1;
    uint8_t ABE : 1;
    uint8_t AA1 : 1;
    uint8_t FST : 1;
    uint8_t CTXT : 1;
    uint8_t FIX : 1;
    uint64_t _PAD0 : 53;
};

// Primitive attribute setting register
struct GnRegPRMODE
{
    uint8_t _PAD0 : 3;
    uint8_t IIP : 1;
    uint8_t TME : 1;
    uint8_t FGE : 1;
    uint8_t ABE : 1;
    uint8_t AA1 : 1;
    uint8_t FST : 1;
    uint8_t CTXT : 1;
    uint8_t FIX : 1;
    uint64_t _PAD1 : 53;
};

// Primitive setting mode register
struct GnRegPRMODECONT
{
    uint8_t AC : 1;
    uint64_t _PAD0 : 63;
};

// Set primitive color (RGBA) and normalized texture coordinate (Q)
struct GnRegRGBAQ
{
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t A;
    float Q;
};

// Set normalized texture coordinates (ST)
struct GnRegST
{
    float S;
    float T;
};

// Set texel coordinates (UV)
struct GnRegUV
{
    uint16_t U : 14;
    uint8_t _PAD0 : 2;
    uint16_t V : 14;
    uint64_t _PAD1 : 34;
};

// Set vertex coordinates (XYZ)
struct GnRegXYZ
{
    uint16_t X;
    uint16_t Y;
    uint32_t Z;
};

// Set vertex coordinates + fog coefficient
struct GnRegXYZF
{
    uint16_t X;
    uint16_t Y;
    uint32_t Z : 24;
    uint8_t F;
};

struct GnRegFOG
{
    uint64_t _PAD0 : 56;
    uint8_t F;
};

struct GnRegFOGCOL
{
    uint8_t FCR;
    uint8_t FCG;
    uint8_t FCB;
    uint64_t _PAD0 : 40;
};

struct GnRegDIMX
{
    uint8_t DM00 : 3;
    uint8_t _PAD0 : 1;
    uint8_t DM01 : 3;
    uint8_t _PAD1 : 1;
    uint8_t DM02 : 3;
    uint8_t _PAD2 : 1;
    uint8_t DM03 : 3;
    uint8_t _PAD3 : 1;
    uint8_t DM10 : 3;
    uint8_t _PAD4 : 1;
    uint8_t DM11 : 3;
    uint8_t _PAD5 : 1;
    uint8_t DM12 : 3;
    uint8_t _PAD6 : 1;
    uint8_t DM13 : 3;
    uint8_t _PAD7 : 1;
    uint8_t DM20 : 3;
    uint8_t _PAD8 : 1;
    uint8_t DM21 : 3;
    uint8_t _PAD9 : 1;
    uint8_t DM22 : 3;
    uint8_t _PAD10 : 1;
    uint8_t DM23 : 3;
    uint8_t _PAD11 : 1;
    uint8_t DM30 : 3;
    uint8_t _PAD12 : 1;
    uint8_t DM31 : 3;
    uint8_t _PAD13 : 1;
    uint8_t DM32 : 3;
    uint8_t _PAD14 : 1;
    uint8_t DM33 : 3;
    uint8_t _PAD15 : 1;
};

struct GnRegDTHE
{
    uint8_t DTHE : 1;
    uint64_t _PAD0 : 63;
};

struct GnRegCOLCLAMP
{
    uint8_t COLCLAMP : 1;
    uint64_t _PAD0 : 63;
};

struct GnRegFINISH
{
    uint64_t _PAD0 : 64;
};

struct GnRegHWREG
{
    uint64_t DATA;
};

struct GnRegLABEL
{
    uint32_t ID;
    uint32_t IDMSK;
};

struct GnRegSIGNAL
{
    uint32_t ID;
    uint32_t IDMSK;
};

struct GnRegTEXA
{
    uint8_t TA0;
    uint8_t _PAD0 : 7;
    uint8_t AEM : 1;
    uint16_t _PAD1;
    uint8_t TA1;
    uint32_t _PAD2 : 24;
};

struct GnRegTEXCLUT
{
    uint8_t CBW : 6;
    uint8_t COU : 6;
    uint16_t COV : 10;
    uint64_t _PAD0 : 42;
};

struct GnRegTEXFLUSH
{
    uint64_t _PAD0;
};

struct GnRegTRXDIR
{
    uint8_t XDIR : 2;
    uint64_t _PAD0 : 64;
};

struct GnRegTRXPOS
{
    uint16_t SSAX : 11;
    uint8_t _PAD0 : 5;
    uint16_t SSAY : 11;
    uint8_t _PAD1 : 5;
    uint16_t DSAX : 11;
    uint8_t _PAD2 : 5;
    uint16_t DSAY : 11;
    uint8_t DIR : 2;
    uint8_t _PAD3 : 3;
};

struct GnRegTRXREG
{
    uint16_t RRW : 12;
    uint32_t _PAD0 : 20;
    uint16_t RRH : 12;
    uint32_t _PAD1 : 20;
};

struct GnRegPABE
{
    uint8_t PABE : 1;
    uint64_t _PAD0 : 63;
};

struct GnRegSCANMSK
{
    uint8_t MSK : 2;
    uint64_t _PAD0 : 62;
};

struct GnGIFTag
{
    uint16_t NLOOP : 15;
    uint8_t EOP : 1;
    uint32_t _PAD0 : 30;
    uint8_t PRE : 1;
    uint16_t PRIM : 11;
    uint8_t FLG : 2;
    uint8_t NREG : 4;
    uint64_t REGS;
};

#pragma pack(pop)

union GnReg64
{
    uint32_t u32[2];
    float f32[2];
    uint64_t u64;

    // Registers
    GnRegPRIM PRIM;
    GnRegRGBAQ RGBAQ;
    GnRegST ST;
    GnRegUV UV;
    GnRegXYZF XYZF;
    GnRegXYZ XYZ;
    GnRegTEX0 TEX0;
    GnRegCLAMP CLAMP;
    GnRegFOG FOG;
    GnRegTEX1 TEX1;
    GnRegTEX2 TEX2;
    GnRegXYOFFSET XYOFFSET;
    GnRegPRMODECONT PRMODECONT;
    GnRegPRMODE PRMODE;
    GnRegTEXCLUT TEXCLUT;
    GnRegSCANMSK SCANMSK;
    GnRegMIPTBP1 MIPTBP1;
    GnRegMIPTBP2 MIPTBP2;
    GnRegTEXA TEXA;
    GnRegFOGCOL FOGCOL;
    GnRegTEXFLUSH TEXFLUSH;
    GnRegSCISSOR SCISSOR;
    GnRegALPHA ALPHA;
    GnRegDIMX DIMX;
    GnRegDTHE DTHE;
    GnRegCOLCLAMP COLCLAMP;
    GnRegTEST TEST;
    GnRegPABE PABE;
    GnRegFBA FBA;
    GnRegFRAME FRAME;
    GnRegZBUF ZBUF;
    GnRegTRXPOS TRXPOS;
    GnRegTRXREG TRXREG;
    GnRegTRXDIR TRXDIR;
    GnRegHWREG HWREG;
    GnRegSIGNAL SIGNAL;
    GnRegFINISH FINISH;
    GnRegLABEL LABEL;

    GnReg64(uint64_t u) :
        u64(u)
    {
    }

    GnReg64(const GnReg64& other) :
        u64(other.u64)
    {
    }

    GnReg64& operator=(const GnReg64& other)
    {
        u64 = other.u64;
        return *this;
    }
};

template<class Register>
union GnRegWrap64
{
    GnReg64 r64;
    Register r;

    GnRegWrap64() :
        r64(0)
    {
    }
};

union GnReg128
{
    uint32_t u32[4];
    float f32[4];
    uint64_t u64[2];
    __m128 u128;
};

struct GnDrawEnvState
{
    GnRegWrap64<GnRegTEX0> TEX0;
    GnRegWrap64<GnRegCLAMP> CLAMP;
    GnRegWrap64<GnRegTEX1> TEX1;
    GnRegWrap64<GnRegTEX2> TEX2;
    GnRegWrap64<GnRegXYOFFSET> XYOFFSET;
    GnRegWrap64<GnRegMIPTBP1> MIPTBP1;
    GnRegWrap64<GnRegMIPTBP2> MIPTBP2;
    GnRegWrap64<GnRegSCISSOR> SCISSOR;
    GnRegWrap64<GnRegALPHA> ALPHA;
    GnRegWrap64<GnRegTEST> TEST;
    GnRegWrap64<GnRegFRAME> FRAME;
    GnRegWrap64<GnRegZBUF> ZBUF;
};

struct GnRegState
{
    GnRegWrap64<GnRegPRIM> PRIM;
    GnRegWrap64<GnRegRGBAQ> RGBAQ;
    GnRegWrap64<GnRegST> ST;
    GnRegWrap64<GnRegUV> UV;
    GnRegWrap64<GnRegXYZF> XYZF2;
    GnRegWrap64<GnRegXYZ> XYZ2;
    GnRegWrap64<GnRegFOG> FOG;
    GnRegWrap64<GnRegXYZF> XYZF3;
    GnRegWrap64<GnRegXYZ> XYZ3;
    GnRegWrap64<GnRegPRMODECONT> PRMODECONT;
    GnRegWrap64<GnRegPRMODE> PRMODE;
    GnRegWrap64<GnRegTEXCLUT> TEXCLUT;
    GnRegWrap64<GnRegSCANMSK> SCANMSK;
    GnRegWrap64<GnRegTEXA> TEXA;
    GnRegWrap64<GnRegFOGCOL> FOGCOL;
    GnRegWrap64<GnRegTEXFLUSH> TEXFLUSH;
    GnRegWrap64<GnRegDIMX> DIMX;
    GnRegWrap64<GnRegDTHE> DTHE;
    GnRegWrap64<GnRegCOLCLAMP> COLCLAMP;
    GnRegWrap64<GnRegPABE> PABE;
    GnRegWrap64<GnRegFBA> FBA;
    GnRegWrap64<GnRegTRXPOS> TRXPOS;
    GnRegWrap64<GnRegTRXREG> TRXREG;
    GnRegWrap64<GnRegTRXDIR> TRXDIR;
    GnRegWrap64<GnRegHWREG> HWREG;
    GnRegWrap64<GnRegSIGNAL> SIGNAL;
    GnRegWrap64<GnRegFINISH> FINISH;
    GnRegWrap64<GnRegLABEL> LABEL;
    GnDrawEnvState drawEnv[2];

    GnRegState()
    {
    }
};
