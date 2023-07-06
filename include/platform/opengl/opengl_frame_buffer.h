#pragma once

#include "gauri/renderer/frame_buffer.h"
namespace gauri
{
class OpenGLFrameBuffer : public FrameBuffer
{
  public:
    OpenGLFrameBuffer(const FrameBufferSpecification &spec);
    ~OpenGLFrameBuffer() override;

    void Invalidate();

    void Bind() override;
    void Unbind() override;

    uint32_t GetColorAttachmentRendererID() const override
    {
        return m_ColorAttachment;
    }

    const FrameBufferSpecification &GetSpecification() const override
    {
        return m_Specification;
    }

  private:
    uint32_t m_RendererID = 0;
    uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0;
    FrameBufferSpecification m_Specification;
};
} // namespace gauri
