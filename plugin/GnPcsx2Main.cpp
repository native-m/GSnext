#include <gsnext/GnWindow.h>
#include <gsnext/GnContext.h>
#include <gsnext/GnLog.h>
#include "GnPcsx2Main.h"

static std::shared_ptr<GnWindow> g_window;
GnContext* g_context;

// private functions
static s32 Gn_OpenWindow(void** pDsp, const char* title);

u32 CALLBACK PS2EgetLibType(void)
{
    return PS2E_LT_GS;
}

u32 CALLBACK PS2EgetLibVersion2(u32 type)
{
    const unsigned char version = PS2E_GS_VERSION;
    const unsigned char revision = 1;
    const unsigned char build = 2; // increase that with each version

    return (version << 16) | (revision << 8) | build;
}

const char* CALLBACK PS2EgetLibName(void)
{
    return "GSnext";
}

u32 CALLBACK PS2EgetCpuPlatform()
{
#ifdef _M_AMD64

    return PS2E_X86_64;

#else

    return PS2E_X86;

#endif
}

s32 CALLBACK GSinit()
{
    GnLog::Initialize();
    GnLog::Info("Initializing...");

    return 0;
}

s32 CALLBACK GSopen(void** pDsp, const char* Title, int multithread)
{
    s32 ret = 0;
    GnLog::Info("Initializing Window...");

    ret = Gn_OpenWindow(pDsp, Title);
    g_context = new GnContext();
    g_context->Initialize(g_window);

    return ret;
}

void CALLBACK GSclose()
{
    GnLog::Info("Closing Window...");

    if (g_context) {
        g_context->ResetDevice();
    }

    if (g_window) {
        g_window->Close();
    }
}

void CALLBACK GSshutdown()
{
    GnLog::Info("Closing Window...");

    if (g_context) {
        delete g_context;
        g_context = nullptr;
    }

    if (g_window) {
        g_window->Detach();
    }
}

void CALLBACK GSsetSettingsDir(const char* dir)
{
}

void CALLBACK GSsetLogDir(const char* dir)
{
}

void CALLBACK GSvsync(int field)
{
    g_window->ProcessMessage();
}

void CALLBACK GSgifTransfer(const u32* pMem, u32 size)
{
    assert(g_context != nullptr);
    g_context->Transfer<3>(pMem, size);
}

void CALLBACK GSgifTransfer1(u32* pMem, u32 addr)
{
    assert(g_context != nullptr);
    g_context->Transfer<0>((u32*)((u8*)pMem + addr), (0x4000 - addr) / 16);
}

void CALLBACK GSgifTransfer2(u32* pMem, u32 size)
{
    assert(g_context != nullptr);
    g_context->Transfer<1>(pMem, size);
}

void CALLBACK GSgifTransfer3(u32* pMem, u32 size)
{
    assert(g_context != nullptr);
    g_context->Transfer<2>(pMem, size);
}

void CALLBACK GSgetLastTag(u64* ptag)
{
}

void CALLBACK GSgifSoftReset(u32 mask)
{
}

void CALLBACK GSreadFIFO(u64* mem)
{
}

void CALLBACK GSinitReadFIFO(u64* mem)
{
}

void CALLBACK GSreadFIFO2(u64* mem, int qwc)
{
}

void CALLBACK GSinitReadFIFO2(u64* mem, int qwc)
{
}

void CALLBACK GSkeyEvent(keyEvent* ev)
{
}

void CALLBACK GSchangeSaveState(int, const char* filename)
{
}

void CALLBACK GSmakeSnapshot(char* path)
{
}

void CALLBACK GSmakeSnapshot2(char* pathname, int* snapdone, int savejpg)
{
}

void CALLBACK GSirqCallback(void(*callback)())
{
}

void CALLBACK GSsetBaseMem(void*)
{
}

void CALLBACK GSsetGameCRC(int crc, int gameoptions)
{
}

void CALLBACK GSsetFrameSkip(int frameskip)
{
}

int CALLBACK GSsetupRecording(int start, void* pData)
{
    return 1;
}

void CALLBACK GSreset()
{
}

void CALLBACK GSgetTitleInfo2(char* dest, size_t length)
{
}

void CALLBACK GSwriteCSR(u32 value)
{
}

s32 CALLBACK GSfreeze(int mode, freezeData* data)
{
    return s32();
}

void CALLBACK GSconfigure()
{
}

void CALLBACK GSabout()
{
}

s32 CALLBACK GStest()
{
    return s32();
}

void CALLBACK GSgetDriverInfo(GSdriverInfo* driverInfo)
{
}

// private functions

s32 Gn_OpenWindow(void** pDsp, const char* title)
{
    std::shared_ptr<GnWindow> window;

    if (*pDsp == nullptr) {
        // Old-style API expect us to manage our own window
        window = GnWindow::Create();

        if (!window->Initialize(std::string(title), 640, 480)) {
            return -1;
        }

        window->Open();
        *pDsp = window->GetNativeHandle();
        g_window = window;
    }
    else if (g_window != nullptr && g_window->GetNativeHandle() != nullptr) {
        // Open the window when it's already here...
        g_window->Open();
    }
    else {
        // New PCSX2 expect us to use PCSX2's GS window
        window = GnWindow::CreateManaged();
        window->Attach(*pDsp);
        g_window = window;
    }

    return 0;
}
