#include "grpch.h"

#include "gauri/core/window.h"

#ifdef GR_PLATFORM_WINDOWS
#include "platform/windows/windows_window.h"
#endif

namespace gauri
{
Scope<Window> Window::Create(const WindowProperty &props)
{
#ifdef GR_PLATFORM_WINDOWS
    return CreateScope<WindowsWindow>(props);
#else
    GR_CORE_ASSERT(false, "Unknown platform!");
    return nullptr;
#endif
}

} // namespace gauri
