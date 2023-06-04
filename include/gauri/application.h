/*!
 * \file   application.h
 * \brief
 *
 * \author leeh8
 * \date   May 2023
 */

#pragma once

#include "gauri/event/event.h"
#include "gauri/imgui/imgui_layer.h"
#include "gauri/layer_stack.h"
#include "gauri/window.h"

#include "gauri/renderer/buffer.h"
#include "gauri/renderer/shader.h"
#include "gauri/renderer/vertex_array.h"

namespace gauri
{

class Application
{
  public:
    Application();
    virtual ~Application();

    void Run();

    void OnEvent(Event &e);

    void PushLayer(Layer *layer);
    void PushOverlay(Layer *overlay);

    inline Window &GetWindow()
    {
        return *m_Window;
    }

    static inline Application &Get()
    {
        return *s_Instance;
    }

  private:
    bool OnWindowClose(WindowCloseEvent &e);

    bool m_IsRunning = true;
    std::unique_ptr<Window> m_Window = nullptr;
    ImGuiLayer *m_ImGuiLayer = nullptr;
    LayerStack m_LayerStack{};

    static Application *s_Instance;

    std::shared_ptr<Shader> m_Shader = nullptr;
    std::shared_ptr<VertexArray> m_VertexArray = nullptr;
    std::shared_ptr<VertexBuffer> m_VertexBuffer = nullptr;
    std::shared_ptr<IndexBuffer> m_IndexBuffer = nullptr;

    std::shared_ptr<Shader> m_BlueShader = nullptr;
    std::shared_ptr<VertexArray> m_SquareVA = nullptr;
};

Application *CreateApplication();

} // namespace gauri
