#pragma once

#include "gauri/core.h"

namespace gauri
{
class Input
{
  public:
    inline static bool IsKeyPressed(int32_t keycode)
    {
        return s_Instance->IsKeyPressedImpl(keycode);
    }

    inline static bool IsMouseButtonPressed(int32_t button)
    {
        return s_Instance->IsMouseButtonPressedImpl(button);
    }

    inline static bool GetMouseX()
    {
        return s_Instance->GetMouseXImpl();
    }
    inline static bool GetMouseY()
    {
        return s_Instance->GetMouseYImpl();
    }

  protected:
    virtual bool IsKeyPressedImpl(int32_t keycode) = 0;
    virtual bool IsMouseButtonPressedImpl(int32_t button) = 0;
    virtual bool GetMouseXImpl() = 0;
    virtual bool GetMouseYImpl() = 0;

  private:
    static Input *s_Instance;
};
} // namespace gauri
