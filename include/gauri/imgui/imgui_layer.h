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
    void OnEvent(Event &e) override;

    void Begin();
    void End();

    void BlockEvents(bool block)
    {
        m_BlockEvents = block;
    }

  private:
    void SetDarkThemeColors();
    bool m_BlockEvents = true;
    float m_Time = 0.0f;
};
} // namespace gauri
