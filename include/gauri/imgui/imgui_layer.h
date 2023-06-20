#pragma once

#include "gauri/core/layer.h"

namespace gauri
{

class ImGuiLayer : public Layer
{
  public:
    ImGuiLayer();
    ~ImGuiLayer() override;

    void OnAttach() override;
    void OnDetach() override;

    void Begin();
    void End();

  private:
    float m_Time = 0.0f;
};
} // namespace gauri
