#include "grpch.h"

#include "gauri/application.h"
#include "platform/windows/windows_input.h"

#include <GLFW/glfw3.h>

namespace gauri
{
Input *Input::s_Instance = new WindowsInput();

bool WindowsInput::IsKeyPressedImpl(int32_t keycode)
{
    auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
    auto state = glfwGetKey(window, keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool WindowsInput::IsMouseButtonPressedImpl(int32_t button)
{
    auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
    auto state = glfwGetMouseButton(window, button);
    return state == GLFW_PRESS;
}

std::pair<float, float> WindowsInput::GetMousePositionImpl()
{
    auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
    double x, y;

    glfwGetCursorPos(window, &x, &y);

    return {static_cast<float>(x), static_cast<float>(y)};
}
float WindowsInput::GetMouseXImpl()
{
    auto [x, y] = GetMousePositionImpl();
    return x;
}
float WindowsInput::GetMouseYImpl()
{
    auto [x, y] = GetMousePositionImpl();
    return x;
}
} // namespace gauri
