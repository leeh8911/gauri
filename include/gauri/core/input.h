#pragma once

#include "gauri/core/base.h"

namespace gauri
{
class Input
{
  public:
    static bool IsKeyPressed(int32_t keycode);

    static bool IsMouseButtonPressed(int32_t button);
    static std::pair<float, float> GetMousePosition();

    static float GetMouseX();
    static float GetMouseY();
};
} // namespace gauri
