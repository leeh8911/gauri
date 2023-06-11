#include "grpch.h"

#include "platform/opengl/opengl_renderer_api.h"

#include <glad/glad.h>

namespace gauri
{
void OpenGLRendererAPI::Init()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OpenGLRendererAPI::SetClearColor(const glm::vec4 &color)
{
    glClearColor(color.x, color.y, color.z, color.w);
}

void OpenGLRendererAPI::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray> &vertexArray)
{
    glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}
} // namespace gauri