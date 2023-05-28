#pragma once

#include "gauri/layer.h"

namespace gauri
{

class ImGuiLayer : public Layer
{
  public:
    ImGuiLayer();
    ~ImGuiLayer() override;

    void OnAttach() override;
    void OnDetach() override;
    void OnImGuiRender() override;

    void Begin();
    void End();

  private:
    float m_Time = 0.0f;
};
} // namespace gauri
