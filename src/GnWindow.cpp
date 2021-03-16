#include <gsnext/GnWindow.h>
#include "Window/GnWindowWin32.h"
#include "Window/GnManagedWindowWin32.h"

std::shared_ptr<GnWindow> GnWindow::Create()
{
    return std::static_pointer_cast<GnWindow>(std::make_shared<GnWindowWin32>());
}

std::shared_ptr<GnWindow> GnWindow::CreateManaged()
{
    return std::static_pointer_cast<GnWindow>(std::make_shared<GnManagedWindowWin32>());
}
