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
    float m_Time = 0.0f;
};
} // namespace gauri
