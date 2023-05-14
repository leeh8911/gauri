
#include "grpch.h"

#include "gauri/application.h"
#include "gauri/event/event.h"
#include "gauri/logger.h"

namespace gauri
{
Application::Application()
{
}

Application::~Application()
{
}

void Application::Run()
{
    WindowResizeEvent e(1280, 720);
    if (e.IsInCategory(EventCategoryApplication))
    {
        GR_TRACE(e.ToString());
    }
    if (e.IsInCategory(EventCategoryInput))
    {
        GR_TRACE(e.ToString());
    }

    while (m_IsRunning)
        ;
}

} // namespace gauri
