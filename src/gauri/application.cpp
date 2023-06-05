/*!
 * @file application.cpp
 * @author Sangwon Lee
 * @brief
 * @version 0.1
 * @date 2023-05-30
 *
 * @copyright Copyright (c) 2023
 */

#include "grpch.h"

#include "gauri/application.h"
#include "gauri/core.h"
#include "gauri/event/event.h"
#include "gauri/input.h"
#include "gauri/logger.h"
#include "gauri/renderer/renderer.h"

// clang-format off
#include <glad/glad.h>
// clang-format on

namespace gauri
{
Application *Application::s_Instance = nullptr;

Application::Application()
{
    GR_CORE_ASSERT(!s_Instance, "Application already exists!")
    s_Instance = this;

    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(GR_BIND_EVENT_FN(Application::OnEvent));

    m_ImGuiLayer = new ImGuiLayer();
    PushOverlay(m_ImGuiLayer);

    m_VertexArray.reset(VertexArray::Create());

    // clang-format off
    // triangle {x, y, z}
    float vertices[3 * 7] = {-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
                              0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f, 
                              0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f};
    // clang-format on

    std::shared_ptr<VertexBuffer> vertexBuffer;
    vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

    BufferLayout layout = {{ShaderDataType::Float3, "a_Position"}, {ShaderDataType::Float4, "a_Color"}};
    vertexBuffer->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(vertexBuffer);

    uint32_t indices[3] = {0, 1, 2};
    std::shared_ptr<IndexBuffer> indexBuffer;
    indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
    m_VertexArray->SetIndexBuffer(indexBuffer);

    m_SquareVA.reset(VertexArray::Create());

    // clang-format off
    // triangle {x, y, z}
    float squareVertices[3 * 4] = {-0.75f, -0.75f, 0.0f,
                                    0.75f, -0.75f, 0.0f, 
                                    0.75f, 0.75f, 0.0f, 
                                   -0.75f, 0.75f, 0.0f};
    // clang-format on
    std::shared_ptr<VertexBuffer> squareVB;
    squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
    squareVB->SetLayout({{ShaderDataType::Float3, "a_Position"}});
    m_SquareVA->AddVertexBuffer(squareVB);

    uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
    std::shared_ptr<IndexBuffer> suqareIB;
    suqareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
    m_SquareVA->SetIndexBuffer(suqareIB);

    std::string vertexSrc = R"(
        #version 330 core
        
        layout(location = 0) in vec3 a_Position;        
        layout(location = 1) in vec4 a_Color;        
        
        out vec3 v_Position;
        out vec4 v_Color;

        void main()
        {
            v_Position = a_Position;
            v_Color = a_Color;
            gl_Position = vec4(a_Position, 1.0);
        }
    )";
    std::string framgmentSrc = R"(
        #version 330 core
        
        layout(location = 0) out vec4 color;

        in vec3 v_Position;
        in vec4 v_Color;

        void main()
        {
            color = v_Color;
        }
    )";

    m_Shader.reset(new Shader(vertexSrc, framgmentSrc));

    std::string blueShaderVertexSrc = R"(
        #version 330 core
        
        layout(location = 0) in vec3 a_Position;        
        
        out vec3 v_Position;

        void main()
        {
            v_Position = a_Position;
            gl_Position = vec4(a_Position, 1.0);
        }
    )";
    std::string blueShaderFragmentSrc = R"(
        #version 330 core
        
        layout(location = 0) out vec4 color;

        in vec3 v_Position;

        void main()
        {
            color = vec4(0.2, 0.3, 0.8, 1.0);
        }
    )";

    m_BlueShader.reset(new Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
}

Application::~Application()
{
}

void Application::OnEvent(Event &e)
{
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(GR_BIND_EVENT_FN(Application::OnWindowClose));

    GR_CORE_TRACE("Application::OnEvent: {0}", e.ToString());

    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
    {
        (*--it)->OnEvent(e);
        if (e.IsHandled())
        {
            break;
        }
    }
}

void Application::PushLayer(Layer *layer)
{
    m_LayerStack.PushLayer(layer);
    layer->OnAttach();
}

void Application::PushOverlay(Layer *overlay)
{
    m_LayerStack.PushOverlay(overlay);
    overlay->OnAttach();
}

bool Application::OnWindowClose(WindowCloseEvent & /*e*/)
{
    m_IsRunning = false;
    return false;
}

void Application::Run()
{
    while (m_IsRunning)
    {
        RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        RenderCommand::Clear();

        Renderer::BeginScene();

        m_BlueShader->Bind();
        Renderer::Submit(m_SquareVA);

        m_Shader->Bind();
        Renderer::Submit(m_VertexArray);

        Renderer::EndScene();

        for (Layer *layer : m_LayerStack)
        {
            layer->OnUpdate();
        }

        m_ImGuiLayer->Begin();
        for (Layer *layer : m_LayerStack)
        {
            layer->OnImGuiRender();
        }
        m_ImGuiLayer->End();

        m_Window->OnUpdate();
    }
}

} // namespace gauri
