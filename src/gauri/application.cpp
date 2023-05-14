/*!
 * @file application.cpp
 * @author leeh8
 * @brief
 * @version 0.1
 * @date 2023-05-$DAY
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "grpch.h"

#include "gauri/application.h"
#include "gauri/event/event.h"
#include "gauri/logger.h"

namespace gauri
{
Application::Application()
{
    m_Window = std::unique_ptr<Window>(Window::Create());
}

Application::~Application()
{
}

void Application::Run()
{
    while (m_IsRunning)
    {

        m_Window->OnUpdate();
    }
}

} // namespace gauri
