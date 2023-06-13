/*!
 * \file   application.h
 * \brief
 *
 * \author leeh8
 * \date   May 2023
 */

#pragma once

#include "gauri/core/timestep.h"
#include "gauri/event/event.h"
#include "gauri/imgui/imgui_layer.h"
#include "gauri/layer_stack.h"
#include "gauri/window.h"

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

    Timestep m_Timestep;
    float m_LastFrameTime = 0.0f;

    static Application *s_Instance;
};

Application *CreateApplication();

} // namespace gauri
