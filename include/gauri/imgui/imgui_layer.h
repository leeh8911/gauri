#pragma once

#include "gauri/layer.h"

namespace gauri
{

class ImGuiLayer : public Layer
{
  public:
    ImGuiLayer();
    ~ImGuiLayer() override;

    void OnAttach();
    void OnDetach();
    void OnUpdate();
    void OnEvent(Event &event);

  private:
    bool OnMouseButtonPressedEvent(MouseButtonPressedEvent &e);
    bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &e);
    bool OnMouseMovedEvent(MouseMovedEvent &e);
    bool OnMouseScrolledEvent(MouseScrolledEvent &e);
    bool OnKeyPressedEvent(KeyPressedEvent &e);
    bool OnKeyReleasedEvent(KeyReleasedEvent &e);
    bool OnKeyTypedEvent(KeyTypedEvent &e);
    bool OnWindowResizeEvent(WindowResizeEvent &e);
    float m_Time = 0.0f;
};
} // namespace gauri
