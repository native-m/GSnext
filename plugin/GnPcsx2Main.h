#pragma once

#include <pcsx2/PS2Edefs.h>
#include <Windows.h>

#define PS2E_X86 0x01   // 32 bit
#define PS2E_X86_64 0x02   // 64 bit

struct Pcsx2WinInfo
{
    HWND window;
    HMENU menu;
    HWND statusHwnd;
};

extern "C"
{

// PS2E API
u32 CALLBACK PS2EgetLibType(void);
u32 CALLBACK PS2EgetLibVersion2(u32 type);
const char* CALLBACK PS2EgetLibName(void);
u32 CALLBACK PS2EgetCpuPlatform();

// GS API
s32 CALLBACK GSinit();
s32 CALLBACK GSopen(void** pDsp, const char* Title, int multithread);
void CALLBACK GSclose();
void CALLBACK GSshutdown();
void CALLBACK GSsetSettingsDir(const char* dir);
void CALLBACK GSsetLogDir(const char* dir);
void CALLBACK GSvsync(int field);
void CALLBACK GSgifTransfer(const u32* pMem, u32 addr);
void CALLBACK GSgifTransfer1(u32* pMem, u32 size);
void CALLBACK GSgifTransfer2(u32* pMem, u32 size);
void CALLBACK GSgifTransfer3(u32* pMem, u32 size);
void CALLBACK GSgetLastTag(u64* ptag); // returns the last tag processed (64 bits)
void CALLBACK GSgifSoftReset(u32 mask);
void CALLBACK GSreadFIFO(u64* mem);
void CALLBACK GSinitReadFIFO(u64* mem);
void CALLBACK GSreadFIFO2(u64* mem, int qwc);
void CALLBACK GSinitReadFIFO2(u64* mem, int qwc);

void CALLBACK GSkeyEvent(keyEvent* ev);
void CALLBACK GSchangeSaveState(int, const char* filename);
void CALLBACK GSmakeSnapshot(char* path);
void CALLBACK GSmakeSnapshot2(char* pathname, int* snapdone, int savejpg);
void CALLBACK GSirqCallback(void (*callback)());
void CALLBACK GSsetBaseMem(void*);
void CALLBACK GSsetGameCRC(int crc, int gameoptions);

void CALLBACK GSsetFrameSkip(int frameskip);

int CALLBACK GSsetupRecording(int start, void* pData);

void CALLBACK GSreset();

void CALLBACK GSgetTitleInfo2(char* dest, size_t length);
void CALLBACK GSwriteCSR(u32 value);
s32 CALLBACK GSfreeze(int mode, freezeData* data);
void CALLBACK GSconfigure();
void CALLBACK GSabout();
s32 CALLBACK GStest();
void CALLBACK GSgetDriverInfo(GSdriverInfo* driverInfo);

}
