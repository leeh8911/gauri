/*!
 * @file application.cpp
 * @author Sangwon Lee
 * @brief
 * @version 0.1
 * @date 2023-05-30
 *
 * @copyright Copyright (c) 2023
 */

#include "grpch.h"

#include "gauri/core/application.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "gauri/core/base.h"
#include "gauri/core/input.h"
#include "gauri/core/logger.h"
#include "gauri/core/timestep.h"
#include "gauri/event/event.h"
#include "gauri/renderer/renderer.h"

namespace gauri
{
Application *Application::s_Instance = nullptr;

Application::Application()
{
    GR_PROFILE_FUNCTION();
    GR_CORE_ASSERT(!s_Instance, "Application already exists!")
    s_Instance = this;

    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(GR_BIND_EVENT_FN(Application::OnEvent));

    Renderer::Init();

    m_ImGuiLayer = new ImGuiLayer();
    PushOverlay(m_ImGuiLayer);
}

Application::~Application()
{
    GR_PROFILE_FUNCTION();
}

void Application::OnEvent(Event &e)
{
    GR_PROFILE_FUNCTION();

    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(GR_BIND_EVENT_FN(Application::OnWindowClose));
    dispatcher.Dispatch<WindowResizeEvent>(GR_BIND_EVENT_FN(Application::OnWindowResize));

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
    GR_PROFILE_FUNCTION();

    m_LayerStack.PushLayer(layer);
    layer->OnAttach();
}

void Application::PushOverlay(Layer *overlay)
{
    GR_PROFILE_FUNCTION();

    m_LayerStack.PushOverlay(overlay);
    overlay->OnAttach();
}

void Application::Close()
{
    m_IsRunning = false;
}

bool Application::OnWindowClose(WindowCloseEvent & /*e*/)
{
    m_IsRunning = false;
    return false;
}
bool Application::OnWindowResize(WindowResizeEvent &e)
{
    GR_PROFILE_FUNCTION();

    if (e.GetWidth() == 0 || e.GetHeight() == 0)
    {
        m_Minimized = true;
        return false;
    }
    m_Minimized = false;
    Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
    return false;
}

void Application::Run()
{
    GR_PROFILE_FUNCTION();

    while (m_IsRunning)
    {
        GR_PROFILE_SCOPE("RunLoop");
        float time = (float)glfwGetTime(); // Platform::GetTime()
        Timestep timestep = time - m_LastFrameTime;
        m_LastFrameTime = time;

        if (!m_Minimized)
        {
            {
                GR_PROFILE_SCOPE("LayerStack OnUpdate");
                for (Layer *layer : m_LayerStack)
                {
                    layer->OnUpdate(timestep);
                }
            }

            m_ImGuiLayer->Begin();
            {
                GR_PROFILE_SCOPE("LayerStack OnImGuiRender");
                for (Layer *layer : m_LayerStack)
                {
                    layer->OnImGuiRender();
                }
            }
            m_ImGuiLayer->End();
        }

        m_Window->OnUpdate();
    }
}

} // namespace gauri
