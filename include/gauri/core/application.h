/*!
 * \file   application.h
 * \brief
 *
 * \author leeh8
 * \date   May 2023
 */

#pragma once

#include "gauri/core/layer_stack.h"
#include "gauri/core/timestep.h"
#include "gauri/core/window.h"
#include "gauri/event/event.h"
#include "gauri/imgui/imgui_layer.h"

namespace gauri
{

class Application
{
  public:
    Application(const std::string &name = "Gauri App");
    virtual ~Application();

    void Run();

    void OnEvent(Event &e);

    void PushLayer(Layer *layer);
    void PushOverlay(Layer *overlay);

    inline Window &GetWindow()
    {
        return *m_Window;
    }

    void Close();

    static inline Application &Get()
    {
        return *s_Instance;
    }

  private:
    bool OnWindowClose(WindowCloseEvent &e);
    bool OnWindowResize(WindowResizeEvent &e);

    bool m_IsRunning = true;
    bool m_Minimized = false;
    Scope<Window> m_Window = nullptr;
    ImGuiLayer *m_ImGuiLayer = nullptr;
    LayerStack m_LayerStack{};

    Timestep m_Timestep;
    float m_LastFrameTime = 0.0f;

    static Application *s_Instance;
};

Application *CreateApplication();

} // namespace gauri
