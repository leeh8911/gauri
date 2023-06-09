#include "grpch.h"

#include "gauri/renderer/texture.h"

#include "gauri/renderer/renderer.h"
#include "platform/opengl/opengl_texture.h"

namespace gauri
{
Ref<Texture2D> Texture2D::Create(const std::string &path)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::None: {
        GR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
    }
    case RendererAPI::API::OpenGL:
        return std::make_shared<OpenGLTexture2D>(path);
    }

    GR_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}
} // namespace gauri
