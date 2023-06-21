/*!
 * @file buffer.cpp
 * @author Sangwon Lee
 * @brief
 * @version 0.1
 * @date 2023-05-30
 *
 * @copyright Copyright (c) 2023
 */

#include "grpch.h"

#include "gauri/renderer/buffer.h"

#include "gauri/core/core.h"
#include "gauri/core/logger.h"
#include "gauri/renderer/renderer.h"
#include "platform/opengl/opengl_buffer.h"

namespace gauri
{
VertexBuffer *VertexBuffer::Create(float *vertices, uint32_t size)
{

    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::None: {
        GR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
    }
    case RendererAPI::API::OpenGL:
        return new OpenGLVertexBuffer(vertices, size);
    }

    GR_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

IndexBuffer *IndexBuffer::Create(uint32_t *indices, uint32_t size)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::None: {
        GR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
    }
    case RendererAPI::API::OpenGL:
        return new OpenGLIndexBuffer(indices, size);
    }

    GR_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}
} // namespace gauri
