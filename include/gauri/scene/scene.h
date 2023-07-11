#pragma once

#include "entt.hpp"

#include "gauri/core/timestep.h"
#include "gauri/scene/component.h"

namespace gauri
{
// forward declaration
class Entity;

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
