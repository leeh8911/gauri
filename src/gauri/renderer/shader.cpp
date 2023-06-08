#include "grpch.h"

#include "gauri/renderer/shader.h"

#include "gauri/core.h"
#include "gauri/renderer/renderer.h"
#include "platform/opengl/opengl_shader.h"

namespace gauri
{

Shader *Shader::Create(const std::string &vertexSrc, const std::string &fragmentSrc)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::None: {
        GR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
    }
    case RendererAPI::API::OpenGL:
        return new OpenGLShader(vertexSrc, fragmentSrc);
    }

    GR_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}
} // namespace gauri
