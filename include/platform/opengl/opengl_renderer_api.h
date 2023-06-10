#pragma once

#include "gauri/renderer/renderer_api.h"

namespace gauri
{
class OpenGLRendererAPI : public RendererAPI
{
  public:
    void Init() override;

    void SetClearColor(const glm::vec4 &color) override;
    void Clear() override;

    void DrawIndexed(const Ref<VertexArray> &vertexArray) override;
};
} // namespace gauri
