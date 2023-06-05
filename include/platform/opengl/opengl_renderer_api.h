#pragma once

#include "gauri/renderer/renderer_api.h"

namespace gauri
{
class OpenGLRendererAPI : public RendererAPI
{
  public:
    void SetClearColor(const Vec4 &color) override;
    void Clear() override;
    void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray) override;
};
} // namespace gauri
