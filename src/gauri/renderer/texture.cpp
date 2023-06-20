#include "grpch.h"

#include "gauri/renderer/texture.h"

#include "gauri/renderer/renderer.h"
#include "platform/opengl/opengl_texture.h"

namespace gauri
{
Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::None: {
        GR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
    }
    case RendererAPI::API::OpenGL:
        return CreateRef<OpenGLTexture2D>(width, height);
    }

    GR_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}
Ref<Texture2D> Texture2D::Create(const std::string &path)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::None: {
        GR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
    }
    case RendererAPI::API::OpenGL:
        return CreateRef<OpenGLTexture2D>(path);
    }

    GR_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}
} // namespace gauri
