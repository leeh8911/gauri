#include "grpch.h"

#include "gauri/renderer/frame_buffer.h"

#include "gauri/renderer/renderer.h"
#include "platform/opengl/opengl_frame_buffer.h"
namespace gauri
{
Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification &spec)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::None: {
        GR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
    }
    case RendererAPI::API::OpenGL:
        return CreateRef<OpenGLFrameBuffer>(spec);
    }

    GR_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

} // namespace gauri
