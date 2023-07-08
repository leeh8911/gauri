#include "grpch.h"

#include "gauri/core/application.h"
#include "gauri/core/input.h"

#include <GLFW/glfw3.h>

namespace gauri
{
bool Input::IsKeyPressed(int32_t keycode)
{
    auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
    auto state = glfwGetKey(window, keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::IsMouseButtonPressed(int32_t button)
{
    auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
    auto state = glfwGetMouseButton(window, button);
    return state == GLFW_PRESS;
}

std::pair<float, float> Input::GetMousePosition()
{
    auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
    double x, y;

    glfwGetCursorPos(window, &x, &y);

    return {static_cast<float>(x), static_cast<float>(y)};
}
float Input::GetMouseX()
{
    auto [x, y] = GetMousePosition();
    return x;
}
float Input::GetMouseY()
{
    auto [x, y] = GetMousePosition();
    return x;
}
} // namespace gauri
