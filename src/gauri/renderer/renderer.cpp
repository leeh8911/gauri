#include "grpch.h"

#include "gauri/renderer/renderer.h"

namespace gauri
{
void Renderer::BeginScene()
{
}

void Renderer::EndScene()
{
}

void Renderer::Submit(const std::shared_ptr<VertexArray> &vertexArray)
{
    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
}
} // namespace gauri
