/*!
 * @file application.cpp
 * @author leeh8
 * @brief
 * @version 0.1
 * @date 2023-05-$DAY
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "grpch.h"

#include "gauri/application.h"
#include "gauri/core.h"
#include "gauri/event/event.h"
#include "gauri/input.h"
#include "gauri/logger.h"

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

namespace gauri
{
Application *Application::s_Instance = nullptr;

Application::Application()
{
    GR_CORE_ASSERT(!s_Instance, "Application already exists!")
    s_Instance = this;

    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(GR_BIND_EVENT_FN(Application::OnEvent));
}

Application::~Application()
{
}

void Application::OnEvent(Event &e)
{
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(GR_BIND_EVENT_FN(Application::OnWindowClose));

    GR_CORE_TRACE("Application::OnEvent: {0}", e.ToString());

    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
    {
        (*--it)->OnEvent(e);
        if (e.IsHandled())
        {
            break;
        }
    }
}

void Application::PushLayer(Layer *layer)
{
    m_LayerStack.PushLayer(layer);
    layer->OnAttach();
}

void Application::PushOverlay(Layer *overlay)
{
    m_LayerStack.PushOverlay(overlay);
    overlay->OnAttach();
}

bool Application::OnWindowClose(WindowCloseEvent & /*e*/)
{
    m_IsRunning = false;
    return false;
}

void Application::Run()
{
    while (m_IsRunning)
    {
        glClearColor(1, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        for (Layer *layer : m_LayerStack)
        {
            layer->OnUpdate();
        }

        auto [x, y] = Input::GetMousePosition();
        GR_CORE_TRACE("{0}, {1}", x, y);
        m_Window->OnUpdate();
    }
}

} // namespace gauri
