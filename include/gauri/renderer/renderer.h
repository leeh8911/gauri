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
    static void Init();
    static void OnWindowResize(uint32_t width, uint32_t height);

    static void BeginScene(OrthographicCamera &camera);
    static void EndScene();
    static void Submit(const Ref<Shader> &shader, const Ref<VertexArray> &vertexArray,
                       const glm::mat4 &transform = glm::mat4(1.0f));

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
