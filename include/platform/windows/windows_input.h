#pragma once

#include "gauri/input.h"

namespace gauri
{
class WindowsInput : public Input
{
  protected:
    bool IsKeyPressedImpl(int32_t keycode) override;
};
} // namespace gauri
