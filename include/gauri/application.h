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

namespace gauri
{

class Application
{
  public:
    Application();
    virtual ~Application();

    void Run();

    void OnEvent(Event &e);

  private:
    bool m_IsRunning = true;
    bool OnWindowClose(WindowCloseEvent &e);
    

    std::unique_ptr<Window> m_Window;
};

Application *CreateApplication();

} // namespace gauri
