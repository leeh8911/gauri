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

    std::string vendor = (char *)glGetString(GL_VENDOR);
    std::string renderer = (char *)glGetString(GL_RENDERER);
    std::string version = (char *)glGetString(GL_VERSION);

    GR_CORE_INFO("OpenGL Info:");
    GR_CORE_INFO("  Vendor: {0}", vendor);
    GR_CORE_INFO("  Renderer: {0}", renderer);
    GR_CORE_INFO("  Version: {0}", version);
}

void OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(m_WindowHandle);
}

} // namespace gauri
