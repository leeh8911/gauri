#include "grpch.h"

#include "platform/opengl/opengl_vertex_array.h"

#include <glad/glad.h>

namespace gauri
{

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
    switch (type)
    {
    case ShaderDataType::Float:
        [[fallthrough]];
    case ShaderDataType::Float2:
        [[fallthrough]];
    case ShaderDataType::Float3:
        [[fallthrough]];
    case ShaderDataType::Float4:
        [[fallthrough]];
    case ShaderDataType::Mat3:
        [[fallthrough]];
    case ShaderDataType::Mat4:
        return GL_FLOAT;
    case ShaderDataType::Int:
        [[fallthrough]];
    case ShaderDataType::Int2:
        [[fallthrough]];
    case ShaderDataType::Int3:
        [[fallthrough]];
    case ShaderDataType::Int4:
        return GL_INT;
    case ShaderDataType::Bool:
        return GL_BOOL;
    }
    GR_CORE_ASSERT(false, "Unknown ShaderDataType!");
    return 0;
}

OpenGLVertexArray::OpenGLVertexArray()
{
    glCreateVertexArrays(1, &m_RendererID);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
    glDeleteVertexArrays(1, &m_RendererID);
}

void OpenGLVertexArray::Bind() const
{
    glBindVertexArray(m_RendererID);
}
void OpenGLVertexArray::Unbind() const
{
    glBindVertexArray(0);
}
void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer)
{
    GR_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

    glBindVertexArray(m_RendererID);
    vertexBuffer->Bind();

    uint32_t index = 0;
    const auto &layout = vertexBuffer->GetLayout();
    for (const auto &element : layout)
    {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type),
                              element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(),
                              (const void *)element.Offset);
        ++index;
    }

    m_VertexBuffers.push_back(vertexBuffer);
}
void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer)
{
    glBindVertexArray(m_RendererID);
    indexBuffer->Bind();

    m_IndexBuffer = indexBuffer;
}
inline const std::vector<std::shared_ptr<VertexBuffer>> &OpenGLVertexArray::GetVertexBuffers() const
{
    return m_VertexBuffers;
}
inline const std::shared_ptr<IndexBuffer> &OpenGLVertexArray::GetIndexBuffer() const
{
    return m_IndexBuffer;
}
} // namespace gauri
