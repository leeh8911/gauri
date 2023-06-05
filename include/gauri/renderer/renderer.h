#pragma once

#include "gauri/renderer/render_command.h"
#include "gauri/renderer/renderer_api.h"

namespace gauri
{

class Renderer
{
  public:
    static void BeginScene();
    static void EndScene();
    static void Submit(const std::shared_ptr<VertexArray> &vertexArray);

    inline static RendererAPI::API GetAPI()
    {
        return RendererAPI::GetAPI();
    };
};
} // namespace gauri
