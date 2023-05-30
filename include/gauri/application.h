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

#include "gauri/renderer/shader.h"

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

    unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
    std::unique_ptr<Shader> m_Shader = nullptr;
};

Application *CreateApplication();

} // namespace gauri
