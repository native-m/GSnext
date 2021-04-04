#include <gsnext/GnContext.h>
#include <gsnext/GnLog.h>
#include <gsnext/Renderer/GnDevice.h>
#include <thread>
#include "ini.h"

GnContext::GnContext()
{
}

GnContext::~GnContext()
{
}

bool GnContext::Open(void** pDsp, const char* title)
{
    LoadConfig();
    CloseConfigWindow();

    std::shared_ptr<GnWindow> window;

    if (*pDsp == nullptr) {
        // Old-style API expect us to manage our own window
        window = GnWindow::Create();

        if (!window->Initialize(std::string(title), 640, 480)) {
            return false;
        }

        window->Open();
        *pDsp = window->GetNativeHandle();
        m_window = window;
    }
    else if (m_window != nullptr && m_window->GetNativeHandle() != nullptr) {
        // Open the window when it's already here...
        m_window->Open();
    }
    else {
        // New PCSX2 expect us to use PCSX2's GS window
        window = GnWindow::CreateManaged();
        window->Attach(*pDsp);
        m_window = window;
    }

    InitDevice();

    return true;
}

void GnContext::Close()
{
    m_window->Close();
}

void GnContext::OpenConfigWindow()
{
}

void GnContext::CloseConfigWindow()
{
    m_configWindowOpened = false;
}

template void GnContext::Transfer<0>(const uint32_t* mem, uint32_t size);
template void GnContext::Transfer<1>(const uint32_t* mem, uint32_t size);
template void GnContext::Transfer<2>(const uint32_t* mem, uint32_t size);
template void GnContext::Transfer<3>(const uint32_t* mem, uint32_t size);

template<uint32_t i>
void GnContext::Transfer(const uint32_t* mem, uint32_t size)
{

}

void GnContext::Vsync()
{
    m_window->ProcessMessage();
}

void GnContext::SetRegsMem(uint32_t* addr)
{
}

void GnContext::SetIniPath(const std::string& path)
{
    m_iniPath = path;
}

std::shared_ptr<GnDevice>& GnContext::GetDevice()
{
    return m_device;
}

bool GnContext::InitDevice()
{
    return false;
}

void GnContext::InitSwapchain()
{
}

void GnContext::LoadConfig()
{
    mINI::INIFile configFile(m_iniPath);
    mINI::INIStructure ini;

    if (!configFile.read(ini)) {
        // Write default config
        ini["adapter"].set({
            {"backend", "vulkan"},
            {"vulkan_adapter", "0"},
            {"d3d12_adapter", "0"}
        });

        ini["graphics"].set({
            {"gpu_palette_conv", "off"},
            {"accurate_date", "off"},
            {"resolution_scale", "1"},
            {"anisotropic_filter", "1"}
        });

        configFile.generate(ini, true);
    }

    // Parse adapter settings
    std::string& backend = ini["adapter"]["backend"];
    std::string& vulkanAdapterId = ini["adapter"]["vulkan_adapter"];
    std::string& d3d12AdapterId = ini["adapter"]["d3d12_adapter"];

    if (backend == "vulkan") {
        m_config.backend = GnBackendRenderer::Vulkan;
    }
    else {
        m_config.backend = GnBackendRenderer::D3D12;
    }

    m_config.vulkanAdapter.FromString(vulkanAdapterId);
    m_config.d3d12Adapter.FromString(d3d12AdapterId);

    // Parse graphics settings
    std::string& gpuPaletteConv = ini["graphics"]["gpu_palette_conv"];
    std::string& accurateDATE = ini["graphics"]["accurate_date"];
    std::string& resolutionScaling = ini["graphics"]["resolution_scale"];
    std::string& anisotropicFilterLevel = ini["graphics"]["anisotropic_filter"];

    m_config.gpuPaletteConv = (gpuPaletteConv == "on") ? true : false;
    m_config.accurateDATE = (accurateDATE == "on") ? true : false;
    m_config.resolutionScaling = std::stoi(resolutionScaling);
    m_config.anisotropicFilterLevel = std::stoi(resolutionScaling);
}

void GnContext::SaveConfig()
{
    mINI::INIFile configFile(m_iniPath);
    mINI::INIStructure ini;

    // Write adapter settings
    mINI::INIMap<std::string>& adapterCfg = ini["adapter"];

    switch (m_config.backend) {
        case GnBackendRenderer::Vulkan:
            adapterCfg["backend"] = "vulkan";
            break;
        case GnBackendRenderer::D3D12:
            adapterCfg["backend"] = "d3d12";
            break;
        case GnBackendRenderer::Metal:
            adapterCfg["backend"] = "metal";
            break;
        default:
            adapterCfg["backend"] = "vulkan";
    }

    adapterCfg["vulkan_adapter"] = m_config.vulkanAdapter.ToString();
    adapterCfg["d3d12_adapter"] = m_config.d3d12Adapter.ToString();

    // Write graphics settings
    mINI::INIMap<std::string>& graphicsCfg = ini["graphics"];

    graphicsCfg["gpu_palette_conv"] = m_config.gpuPaletteConv ? "on" : "off";
    graphicsCfg["accurate_date"] = m_config.accurateDATE ? "on" : "off";
    graphicsCfg["resolution_scale"] = fmt::format("{}", m_config.resolutionScaling);
    graphicsCfg["anisotropic_filter"] = fmt::format("{}", m_config.anisotropicFilterLevel);

    configFile.write(ini, true);
}

void GnContext::ConfigWindowThread()
{
    
}
