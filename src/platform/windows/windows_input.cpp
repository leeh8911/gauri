#include "grpch.h"

#include "gauri/application.h"
#include "platform/windows/windows_input.h"

#include <GLFW/glfw3.h>

namespace gauri
{
bool WindowsInput::IsKeyPressedImpl(int32_t keycode)
{
    auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
    auto state = glfwGetKey(window, keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}
} // namespace gauri
