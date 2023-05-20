
#pragma once

#include <cstdint>
#include <functional>
#include <sstream>
#include <string>

#include "gauri/core.h"

namespace gauri
{

enum class EventType
{
    None = 0,
    WindowClose,
    WindowResize,
    WindowFocus,
    WindowLostFocus,
    WindowMoved,
    AppTick,
    AppUpdate,
    AppRender,
    KeyPressed,
    KeyReleased,
    KeyTyped,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled
};

enum EventCategory
{
    None = 0,
    EventCategoryApplication = bit<0>,
    EventCategoryInput = bit<1>,
    EventCategoryKeyboard = bit<2>,
    EventCategoryMouse = bit<3>,
    EventCategoryMouseButton = bit<4>
};

#define EVENT_CLASS_TYPE(type)                                                                                         \
    static EventType GetStaticType()                                                                                   \
    {                                                                                                                  \
        return EventType::##type;                                                                                      \
    }                                                                                                                  \
    EventType GetEventType() const override                                                                            \
    {                                                                                                                  \
        return GetStaticType();                                                                                        \
    }                                                                                                                  \
    const char *GetName() const override                                                                               \
    {                                                                                                                  \
        return #type;                                                                                                  \
    }

#define EVENT_CLASS_CATEGORY(category)                                                                                 \
    int32_t GetCategoryFlags() const override                                                                          \
    {                                                                                                                  \
        return category;                                                                                               \
    }

class Event
{
    friend class EventDispatcher;

  public:
    virtual EventType GetEventType() const = 0;
    virtual const char *GetName() const = 0;
    virtual int32_t GetCategoryFlags() const = 0;
    virtual std::string ToString() const
    {
        return GetName();
    }

    inline bool IsInCategory(EventCategory category)
    {
        return GetCategoryFlags() & category;
    }

    inline bool IsHandled() const
    {
        return m_Handled;
    }

  protected:
    bool m_Handled = false;
};

class EventDispatcher
{
    template <typename T> using EventFn = std::function<bool(T &)>;

  public:
    EventDispatcher(Event &event) : m_Event(event)
    {
    }

    template <typename T> bool Dispatch(EventFn<T> func)
    {
        if (m_Event.GetEventType() == T::GetStaticType())
        {
            m_Event.m_Handled = func(*(T *)&m_Event);
            return true;
        }
        return false;
    }

  private:
    Event &m_Event;
};

inline std::ostream &operator<<(std::ostream &os, const Event &e)
{
    return os << e.ToString();
}

class KeyEvent : public Event
{
  public:
    inline int32_t GetKeyCode() const
    {
        return m_KeyCode;
    }

    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

  protected:
    KeyEvent(int32_t keycode) : m_KeyCode(keycode)
    {
    }

    int32_t m_KeyCode;
};

class KeyPressedEvent : public KeyEvent
{
  public:
    KeyPressedEvent(int32_t keycode, int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount)
    {
    }

    inline int32_t GetRepeatCount() const
    {
        return m_RepeatCount;
    }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << m_KeyCode << "(" << m_RepeatCount << " repeats)";
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyPressed);

  private:
    int32_t m_RepeatCount;
};

class KeyTypedEvent : public KeyEvent
{
  public:
    KeyTypedEvent(int32_t keycode) : KeyEvent(keycode)
    {
    }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "KeyTypedEvent: " << m_KeyCode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyTyped);

  private:
};

class KeyReleasedEvent : public KeyEvent
{
  public:
    KeyReleasedEvent(int32_t keycode) : KeyEvent(keycode)
    {
    }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << m_KeyCode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyReleased);
};

class MouseMovedEvent : public Event
{
  public:
    MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y)
    {
    }

    inline float GetX() const
    {
        return m_MouseX;
    }

    inline float GetY() const
    {
        return m_MouseY;
    }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
        return ss.str();
    }
    EVENT_CLASS_TYPE(MouseMoved);
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

  private:
    float m_MouseX;
    float m_MouseY;

  private:
};

class MouseScrolledEvent : public Event
{
  public:
    MouseScrolledEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset)
    {
    }

    inline float GetXOffset() const
    {
        return m_XOffset;
    }
    inline float GetYOffset() const
    {

        return m_YOffset;
    }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

  private:
    float m_XOffset, m_YOffset;
};

class MouseButtonEvent : public Event
{
  public:
    inline int GetMouseButton() const
    {
        return m_Button;
    }

    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

  protected:
    MouseButtonEvent(int button) : m_Button{button}
    {
    }
    int m_Button;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
  public:
    MouseButtonPressedEvent(int button) : MouseButtonEvent(button)
    {
    }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << m_Button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
  public:
    MouseButtonReleasedEvent(int button) : MouseButtonEvent(button)
    {
    }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << m_Button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonReleased)
};

class WindowResizeEvent : public Event
{
  public:
    WindowResizeEvent(uint32_t width, uint32_t height) : m_Width(width), m_Height(height)
    {
    }

    inline uint32_t GetWidth() const
    {
        return m_Width;
    }

    inline uint32_t GetHeight() const
    {
        return m_Height;
    }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
        return ss.str();
    }

    EVENT_CLASS_TYPE(WindowResize)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)

  private:
    uint32_t m_Width, m_Height;
};

class WindowCloseEvent : public Event
{
  public:
    WindowCloseEvent()
    {
    }

    EVENT_CLASS_TYPE(WindowClose)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class AppTickEvent : public Event
{
  public:
    AppTickEvent()
    {
    }

    EVENT_CLASS_TYPE(AppTick)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class AppUpdateEvent : public Event
{
  public:
    AppUpdateEvent()
    {
    }

    EVENT_CLASS_TYPE(AppUpdate)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class AppRenderEvent : public Event
{
  public:
    AppRenderEvent()
    {
    }

    EVENT_CLASS_TYPE(AppRender)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

} // namespace gauri
