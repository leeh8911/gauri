/*!
 * \file   application.h
 * \brief
 *
 * \author leeh8
 * \date   May 2023
 */

#pragma once

#include "gauri/window.h"

namespace gauri
{

class Application
{
  public:
    Application();
    virtual ~Application();

    void Run();

  private:
    bool m_IsRunning = true;

    std::unique_ptr<Window> m_Window;
};

Application *CreateApplication();

} // namespace gauri
