#pragma once

#include "gauri/renderer/vertex_array.h"

namespace gauri
{

class OpenGLVertexArray : public VertexArray
{
  public:
    OpenGLVertexArray();
    ~OpenGLVertexArray() override;

    void Bind() const override;
    void Unbind() const override;

    void AddVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) override;
    void SetIndexBuffer(const Ref<IndexBuffer> &indexBuffer) override;

    const std::vector<Ref<VertexBuffer>> &GetVertexBuffers() const override;
    const Ref<IndexBuffer> &GetIndexBuffer() const override;

  private:
    uint32_t m_RendererID;
    std::vector<Ref<VertexBuffer>> m_VertexBuffers;
    Ref<IndexBuffer> m_IndexBuffer;
};
} // namespace gauri
