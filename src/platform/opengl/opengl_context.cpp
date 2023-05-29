#include "grpch.h"

#include "platform/opengl/opengl_context.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "gauri/core.h"
#include "gauri/logger.h"

namespace gauri
{
OpenGLContext::OpenGLContext(GLFWwindow *windowHandle) : m_WindowHandle(windowHandle)
{
    GR_CORE_ASSERT(windowHandle, "Widnow handle is null!");
}
void OpenGLContext::Init()
{
    glfwMakeContextCurrent(m_WindowHandle);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    GR_CORE_ASSERT(status, "Failed to initialize Glad!");
}

void OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(m_WindowHandle);
}

} // namespace gauri
