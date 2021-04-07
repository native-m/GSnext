#include <gsnext/GnWindow.h>
#include <gsnext/GnContext.h>
#include <gsnext/GnLog.h>
#include "GnPcsx2Main.h"

static std::shared_ptr<GnWindow> g_window;
static std::shared_ptr<GnContext> g_context;

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

    if (!g_context) {
        GnLog::Info("Initializing...");

        g_context = std::make_shared<GnContext>();
        g_context->SetIniPath("inis/GSnext.ini");
    }

    return 0;
}

s32 CALLBACK GSopen(void** pDsp, const char* Title, int multithread)
{
    s32 ret = 0;
    GnLog::Info("Initializing Window...");

    g_context->Open(pDsp, Title);

    return ret;
}

void CALLBACK GSclose()
{
    GnLog::Info("Closing Window...");

    if (g_context) {
        g_context->Close();
    }
}

void CALLBACK GSshutdown()
{
    GnLog::Info("Closing Window...");
}

void CALLBACK GSsetSettingsDir(const char* dir)
{
    if (g_context) {
        g_context->SetIniPath(dir);
    }
}

void CALLBACK GSsetLogDir(const char* dir)
{
}

void CALLBACK GSvsync(int field)
{
    g_context->ProcessWindowMessages();
    g_context->Vsync();
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
    GSinit();
    g_context->OpenConfigWindow();
}

void CALLBACK GSabout()
{
}

s32 CALLBACK GStest()
{
    return 0;
}

void CALLBACK GSgetDriverInfo(GSdriverInfo* driverInfo)
{
}

s32 CALLBACK GSnextTest()
{
    void* wnd = nullptr;

    GSinit();
    GSopen(&wnd, "GSnext Test", 0);
    
    while (g_context->ProcessWindowMessages()) {
        g_context->Vsync();
    }

    GSclose();
    GSshutdown();

    return 0;
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
