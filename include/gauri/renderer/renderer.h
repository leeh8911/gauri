#pragma once

#include "gauri/renderer/orthographic_camera.h"
#include "gauri/renderer/render_command.h"
#include "gauri/renderer/renderer_api.h"
#include "gauri/renderer/shader.h"

namespace gauri
{

class Renderer
{
  public:
    static void BeginScene(OrthographicCamera &camera);
    static void EndScene();
    static void Submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray);

    inline static RendererAPI::API GetAPI()
    {
        return RendererAPI::GetAPI();
    };

  private:
    struct SceneData
    {
        glm::mat4 ViewProjectionMatrix;
    };
    static SceneData *m_SceneData;
};
} // namespace gauri
