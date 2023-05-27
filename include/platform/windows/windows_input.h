#pragma once

#include "gauri/input.h"

namespace gauri
{
class WindowsInput : public Input
{
  protected:
    bool IsKeyPressedImpl(int32_t keycode) override;

    bool IsMouseButtonPressedImpl(int32_t button) override;

    float GetMouseXImpl() override;

    float GetMouseYImpl() override;

    std::pair<float, float> GetMousePositionImpl() override;
};
} // namespace gauri
