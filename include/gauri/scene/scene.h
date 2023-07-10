#pragma once

#include "entt.hpp"

#include "gauri/core/timestep.h"
#include "gauri/scene/component.h"
#include "gauri/scene/entity.h"

namespace gauri
{
class Scene
{
  public:
    Scene();
    ~Scene();

    Entity CreateEntity(const std::string &name = std::string());

    // TEMP
    entt::registry &Reg()
    {
        return m_Registry;
    }

    void OnUpdate(Timestep ts);

  private:
    entt::registry m_Registry{};

    friend class Entity;
};
} // namespace gauri
