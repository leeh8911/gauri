#pragma once

#include "gauri/core.h"
#include "gauri/layer.h"

#include <vector>

namespace gauri
{
class LayerStack
{
  public:
    LayerStack();
    ~LayerStack();

    void PushLayer(Layer *layer);
    void PushOverlay(Layer *overlay);
    void PopLayer(Layer *layer);
    void PopOverlay(Layer *overlay);

    std::vector<Layer *>::iterator begin() // NOLINT
    {
        return m_Layers.begin();
    }

    std::vector<Layer *>::iterator end() 
    {
        return m_Layers.end();
    }

  private:
    std::vector<Layer *> m_Layers;
    std::vector<Layer *>::iterator m_LayerInsert;
};
} // namespace gauri
