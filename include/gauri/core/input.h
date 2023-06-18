#pragma once

#include "gauri/core/core.h"

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

    inline static float GetMouseX()
    {
        return s_Instance->GetMouseXImpl();
    }
    inline static float GetMouseY()
    {
        return s_Instance->GetMouseYImpl();
    }
    inline static std::pair<float, float> GetMousePosition()
    {
        return s_Instance->GetMousePositionImpl();
    }

  protected:
    virtual bool IsKeyPressedImpl(int32_t keycode) = 0;
    virtual bool IsMouseButtonPressedImpl(int32_t button) = 0;
    virtual float GetMouseXImpl() = 0;
    virtual float GetMouseYImpl() = 0;
    virtual std::pair<float, float> GetMousePositionImpl() = 0;

  private:
    static Input *s_Instance;
};
} // namespace gauri
