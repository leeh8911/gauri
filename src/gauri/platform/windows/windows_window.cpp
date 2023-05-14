/*!
 * @file windows_window.cpp
 * @author leeh8
 * @brief
 * @version 0.1
 * @date 2023-05-15
 *
 * @copyright Copyright (c) 2023
 */

#include "grpch.h"

#include "gauri/core.h"
#include "gauri/logger.h"
#include "gauri/platform/windows/windows_window.h"

namespace gauri
{
static bool s_GLFWInitialized = false;

Window *Window::Create(const WindowProperty &props)
{
    return new WindowsWindow(props);
}

WindowsWindow::WindowsWindow(const WindowProperty &props)
{
    Init(props);
}

void WindowsWindow::Init(const WindowProperty &props)
{
    m_Data.Title = props.Title;
    m_Data.Width = props.Width;
    m_Data.Height = props.Height;

    GR_CORE_INFO("Create window {0} ({1}, {2})", props.Title, props.Width, props.Height);

    if (!s_GLFWInitialized)
    {
        int32_t success = glfwInit();
        GR_CORE_ASSERT(success, "Could not initialize GFLW!");

        s_GLFWInitialized = true;
    }
    m_Window = glfwCreateWindow((int)(props.Width), (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
    if (m_Window == nullptr)
    {
        GR_CORE_ASSERT(false, "Could not create GLFW Window!");
    }
    glfwMakeContextCurrent(m_Window);
    glfwSetWindowUserPointer(m_Window, &m_Data);
    SetVSync(true);
}

WindowsWindow::~WindowsWindow()
{
    Shutdown();
}

void WindowsWindow::Shutdown()
{
    glfwDestroyWindow(m_Window);
}

void WindowsWindow::OnUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
}

void WindowsWindow::SetVSync(bool enabled)
{
    if (enabled)
    {
        glfwSwapInterval(1);
    }
    else
    {
        glfwSwapInterval(0);
    }

    m_Data.VSync = enabled;
}

bool WindowsWindow::IsVSync() const
{
    return m_Data.VSync;
}

} // namespace gauri
