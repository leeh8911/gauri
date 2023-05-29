#pragma once

#include "gauri/renderer/graphics_context.h"

struct GLFWwindow;

namespace gauri
{
class OpenGLContext : public GraphicsContext
{
  public:
    OpenGLContext(GLFWwindow *windowHandle);

    void Init() override;
    void SwapBuffers() override;

  private:
    GLFWwindow *m_WindowHandle;
};
} // namespace gauri
