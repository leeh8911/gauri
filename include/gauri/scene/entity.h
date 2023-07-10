#pragma once

#include "entt.hpp"

#include "gauri/core/base.h"
#include "gauri/scene/scene.h"

namespace gauri
{
class Entity
{
  public:
    Entity() = default;
    Entity(entt::entity handle, Scene *scene);
    Entity(const Entity &other) = default;

    template <typename T, typename... Args> T &AddComponent(Args &&...args)
    {
        GR_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
        return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
    }

    template <typename T> T &GetComponent()
    {
        GR_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
        return m_Scene->m_Registry.get<T>(m_EntityHandle);
    }

    template <typename T> bool HasComponent()
    {
        return m_Scene->m_Registry.all_of<T>(m_EntityHandle);
    }

    template <typename T> void RemoveComponent()
    {
        GR_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
        m_Scene->m_Registry.remove<T>(m_EntityHandle);
    }

    operator bool() const
    {
        return m_EntityHandle != static_cast<entt::entity>(0);
    }

  private:
    entt::entity m_EntityHandle{};
    Scene *m_Scene = nullptr;
};
} // namespace gauri
