/*!
 * @file windows_window.h
 * @author leeh8
 * @brief
 * @version 0.1
 * @date 2023-05-15
 *
 * @copyright Copyright (c) 2023
 */

#pragma once

#include "gauri/core/window.h"

#include <GLFW/glfw3.h>

#include "gauri/renderer/graphics_context.h"

namespace gauri
{
class WindowsWindow : public Window
{
  public:
    WindowsWindow(const WindowProperty &props);
    ~WindowsWindow() override;

    void OnUpdate() override;

    inline uint32_t GetWidth() const override
    {
        return m_Data.Width;
    }
    inline uint32_t GetHeight() const override
    {
        return m_Data.Height;
    }

    inline void SetEventCallback(const EventCallbackFn &callback) override
    {
        m_Data.EventCallback = callback;
    }
    void SetVSync(bool enabled) override;
    bool IsVSync() const override;

    inline void *GetNativeWindow() const override
    {
        return m_Window;
    }

  private:
    virtual void Init(const WindowProperty &props);
    virtual void Shutdown();

    struct WindowData
    {
        std::string Title;
        uint32_t Width, Height;
        bool VSync;
        EventCallbackFn EventCallback;
    };

    GLFWwindow *m_Window;
    WindowData m_Data;

    GraphicsContext *m_Context;
};
} // namespace gauri
