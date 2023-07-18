﻿/*!
 * @file window.h
 * @author leeh8
 * @brief
 * @version 0.1
 * @date 2023-05-$DAY
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <cstdint>
#include <functional>
#include <string>

#include "gauri/event/event.h"

namespace gauri
{
struct WindowProperty
{
    std::string Title;
    uint32_t Width;
    uint32_t Height;

    WindowProperty(const std::string &title = "Gauri Engine", uint32_t width = 1600, uint32_t height = 900)
        : Title(title), Width(width), Height(height)
    {
    }
};

class Window
{
  public:
    using EventCallbackFn = std::function<void(Event &)>;

    virtual ~Window() = default;

    virtual void OnUpdate() = 0;

    virtual uint32_t GetWidth() const = 0;
    virtual uint32_t GetHeight() const = 0;

    virtual void SetEventCallback(const EventCallbackFn &callback) = 0;
    virtual void SetVSync(bool enabled) = 0;
    virtual bool IsVSync() const = 0;

    virtual void *GetNativeWindow() const = 0;

    static Scope<Window> Create(const WindowProperty &props = WindowProperty());
};
} // namespace gauri
