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

#include "platform/windows/windows_window.h"

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "gauri/core/base.h"
#include "gauri/core/logger.h"
#include "gauri/event/event.h"
#include "platform/opengl/opengl_context.h"

namespace gauri
{
static bool s_GLFWInitialized = false;

static void GLFWErrorCallback(int error, const char *description)
{
    GR_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

Window *Window::Create(const WindowProperty &props)
{
    return new WindowsWindow(props);
}

WindowsWindow::WindowsWindow(const WindowProperty &props)
{
    GR_PROFILE_FUNCTION();

    Init(props);
}

void WindowsWindow::Init(const WindowProperty &props)
{
    GR_PROFILE_FUNCTION();

    m_Data.Title = props.Title;
    m_Data.Width = props.Width;
    m_Data.Height = props.Height;

    GR_CORE_INFO("Create window {0} ({1}, {2})", props.Title, props.Width, props.Height);

    // To be

    if (!s_GLFWInitialized)
    {
        GR_PROFILE_SCOPE("glfwInit");
        int32_t success = glfwInit();
        GR_CORE_ASSERT(success, "Could not initialize GFLW!");
        glfwSetErrorCallback(GLFWErrorCallback);
        s_GLFWInitialized = true;
    }

    {
        GR_PROFILE_SCOPE("glfwCreateWindow");
        m_Window = glfwCreateWindow((int)(props.Width), (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
    }

    m_Context = new OpenGLContext(m_Window);
    m_Context->Init();

    glfwSetWindowUserPointer(m_Window, &m_Data);
    SetVSync(true);

    // Set GLFW callbacks
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
        data.Width = width;
        data.Height = height;

        WindowResizeEvent event(width, height);
        data.EventCallback(event);
    });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        data.EventCallback(event);
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int /*scancode*/, int action, int /*mods*/) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        switch (action)
        {
        case GLFW_PRESS: {
            KeyPressedEvent event(key, 0);
            data.EventCallback(event);
            break;
        }
        case GLFW_RELEASE: {
            KeyReleasedEvent event(key);
            data.EventCallback(event);
            break;
        }
        case GLFW_REPEAT: {
            KeyPressedEvent event(key, 1);
            data.EventCallback(event);
            break;
        }
        default: {
            break;
        }
        }
    });

    glfwSetCharCallback(m_Window, [](GLFWwindow *window, unsigned int keycode) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
        KeyTypedEvent event(keycode);
        data.EventCallback(event);
    });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button, int action, int /*mods*/) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
        switch (action)
        {
        case GLFW_PRESS: {
            MouseButtonPressedEvent event(button);
            data.EventCallback(event);
            break;
        }
        case GLFW_RELEASE: {
            MouseButtonReleasedEvent event(button);
            data.EventCallback(event);
            break;
        }
        default: {
            break;
        }
        }
    });

    glfwSetScrollCallback(m_Window, [](GLFWwindow *window, double xOffset, double yOffset) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
        MouseScrolledEvent event((float)xOffset, (float)yOffset);
        data.EventCallback(event);
    });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double xPos, double yPos) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
        MouseMovedEvent event((float)xPos, (float)yPos);
        data.EventCallback(event);
    });
}

WindowsWindow::~WindowsWindow()
{
    GR_PROFILE_FUNCTION();

    Shutdown();
}

void WindowsWindow::Shutdown()
{
    GR_PROFILE_FUNCTION();

    glfwDestroyWindow(m_Window);
}

void WindowsWindow::OnUpdate()
{
    GR_PROFILE_FUNCTION();

    glfwPollEvents();
    m_Context->SwapBuffers();
}

void WindowsWindow::SetVSync(bool enabled)
{
    GR_PROFILE_FUNCTION();

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
