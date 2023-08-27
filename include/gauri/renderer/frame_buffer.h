#pragma once

#include "gauri/core/base.h"
#include "gauri/core/logger.h"

namespace gauri
{

enum class FrameBufferTextureFormat
{
    None = 0,

    // Color
    RGBA8,

    // Depth/stencil
    DEPTH24STENCIL8,

    // Defaults
    Depth = DEPTH24STENCIL8,
};

struct FrameBufferTextureSpecification
{
    FrameBufferTextureSpecification() = default;
    FrameBufferTextureSpecification(FrameBufferTextureFormat format) : TextureFormat(format)
    {
    }

    FrameBufferTextureFormat TextureFormat{FrameBufferTextureFormat::None};
    // TODO: filtering wrap
};

struct FrameBufferAttachmentSpecification
{
    FrameBufferAttachmentSpecification() = default;
    FrameBufferAttachmentSpecification(std::initializer_list<FrameBufferTextureSpecification> attachments)
        : Attachments(attachments)
    {
    }

    std::vector<FrameBufferTextureSpecification> Attachments{};
};

struct FrameBufferSpecification
{
    uint32_t Width{}, Height{};
    FrameBufferAttachmentSpecification Attachments{};
    uint32_t Samples = 1;
    bool SwapChainTarget = false;
};

class FrameBuffer
{
  public:
    virtual ~FrameBuffer() = default;

    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual void Resize(uint32_t width, uint32_t height) = 0;

    virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const = 0;
    virtual const FrameBufferSpecification &GetSpecification() const = 0;

    static Ref<FrameBuffer> Create(const FrameBufferSpecification &spec);

  private:
};
} // namespace gauri
