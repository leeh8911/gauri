#pragma once

#include "gauri/core/base.h"
#include "gauri/core/logger.h"

namespace gauri
{

struct FrameBufferSpecification
{
    uint32_t Width, Height;
    uint32_t Samples = 1;
    bool SwapChainTarget = false;
};

class FrameBuffer
{
  public:
    virtual ~FrameBuffer() = default;

    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual uint32_t GetColorAttachmentRendererID() const = 0;
    virtual const FrameBufferSpecification &GetSpecification() const = 0;

    static Ref<FrameBuffer> Create(const FrameBufferSpecification &spec);

  private:
};
} // namespace gauri
