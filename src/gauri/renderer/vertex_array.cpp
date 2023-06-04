#include "grpch.h"

#include "gauri/renderer/vertex_array.h"

#include "gauri/renderer/renderer.h"
#include "platform/opengl/opengl_vertex_array.h"

namespace gauri
{
VertexArray *VertexArray::Create()
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::None: {
        GR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
    }
    case RendererAPI::OpenGL:
        return new OpenGLVertexArray();
    }

    GR_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}
} // namespace gauri
