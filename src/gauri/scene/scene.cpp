#include "grpch.h"

#include "gauri/scene/scene.h"

#include <glm/glm.hpp>

#include "gauri/renderer/renderer.h"
#include "gauri/renderer/renderer_2d.h"
#include "gauri/scene/component.h"

namespace gauri
{
static void DoMath(const glm::mat4 &transform)
{
}

static void OnTransformComponent(entt::registry &registry, entt::entity entity)
{
}

Scene::Scene()
{
#if ENTT_EXAMPLE_CODE
    entt::entity entity = m_Registry.create();
    m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));

    m_Registry.on_construct<TransformComponent>().connect<OnTransformComponent>(entity);

    // if (m_Registry.has<TransformComponent>(entity))
    //{
    //     TransformComponent &transform = m_Registry.get<TransformComponent>(entity);
    // }

    auto view = m_Registry.view<TransformComponent>();
    for (auto entity : view)
    {
        TransformComponent &transform = m_Registry.get<TransformComponent>(entity);
    }

    auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);
// for (auto entity : group)
//{
//     auto &[transform, mesh] = m_Registry.get<TransformComponent, MeshComponent>(entity);

//    Renderer::Submit(mesh, transform);
//}
#endif
}

Scene::~Scene()
{
}
entt::entity Scene::CreateEntity()
{
    return m_Registry.create();
}
void Scene::OnUpdate(Timestep ts)
{

    auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
    for (auto entity : group)
    {
        const auto &[transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

        Renderer2D::DrawQuad(transform, sprite.Color);
    }
}
} // namespace gauri
