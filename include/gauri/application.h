/*!
 * \file   application.h
 * \brief
 *
 * \author leeh8
 * \date   May 2023
 */

#pragma once

#include "gauri/window.h"
#include "gauri/event/event.h"
#include "gauri/layer_stack.h"

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

  private:
    bool OnWindowClose(WindowCloseEvent &e);
    
    bool m_IsRunning = true;
    std::unique_ptr<Window> m_Window = nullptr;
    LayerStack m_LayerStack{};
};

Application *CreateApplication();

} // namespace gauri
