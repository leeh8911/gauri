/*!
 * \file   application.h
 * \brief
 *
 * \author leeh8
 * \date   May 2023
 */

#pragma once

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
};

} // namespace gauri
