#include <gsnext/GnContext.h>

GnContext::GnContext()
{
}

GnContext::~GnContext()
{
}

bool GnContext::Initialize(std::shared_ptr<GnWindow>& window)
{
    m_window = window;
    return false;
}

void GnContext::OpenConfigWindow()
{
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
}

void GnContext::ResetDevice()
{
}
