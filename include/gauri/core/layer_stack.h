#pragma once

#include "gauri/core/base.h"
#include "gauri/core/layer.h"

#include <vector>

namespace gauri
{
class LayerStack
{
  public:
    LayerStack() = default;
    ~LayerStack();

    void PushLayer(Layer *layer);
    void PushOverlay(Layer *overlay);
    void PopLayer(Layer *layer);
    void PopOverlay(Layer *overlay);

    inline std::vector<Layer *>::iterator begin() // NOLINT
    {
        return m_Layers.begin();
    }
    inline std::vector<Layer *>::iterator end()
    {
        return m_Layers.end();
    }
    inline std::vector<Layer *>::reverse_iterator rbegin() // NOLINT
    {
        return m_Layers.rbegin();
    }

    inline std::vector<Layer *>::reverse_iterator rend()
    {
        return m_Layers.rend();
    }

  private:
    std::vector<Layer *> m_Layers{};
    uint32_t m_LayerInsertIndex = 0;
};
} // namespace gauri
