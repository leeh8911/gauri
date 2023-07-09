#pragma once

#include "entt.hpp"

#include "gauri/core/timestep.h"
#include "gauri/scene/component.h"

namespace gauri
{
class Scene
{
  public:
    Scene();
    ~Scene();

    entt::entity CreateEntity();

    // TEMP
    entt::registry &Reg()
    {
        return m_Registry;
    }

    void OnUpdate(Timestep ts);

  private:
    entt::registry m_Registry{};
};
} // namespace gauri
