#include "grpch.h"

#include "gauri/scene/entity.h"

namespace gauri
{
Entity::Entity(entt::entity handle, Scene *scene) : m_EntityHandle(handle), m_Scene(scene)
{
}
} // namespace gauri
