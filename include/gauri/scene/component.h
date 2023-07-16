#pragma once

#include <glm/glm.hpp>

#include "gauri/scene/scene_camera.h"
#include "gauri/scene/scriptable_entity.h"

namespace gauri
{
struct TagComponent
{
    std::string Tag;
    TagComponent() = default;
    TagComponent(const TagComponent &) = default;
    TagComponent(const std::string &tag) : Tag(tag)
    {
    }
};
struct TransformComponent
{
    glm::mat4 Transform{1.0f};

    TransformComponent() = default;
    TransformComponent(const TransformComponent &) = default;
    TransformComponent(const glm::mat4 &transform) : Transform(transform)
    {
    }

    operator const glm::mat4 &() const
    {
        return Transform;
    }
    operator glm::mat4 &()
    {
        return Transform;
    }
};
struct SpriteRendererComponent
{
    glm::vec4 Color = {1.0f, 1.0f, 1.0f, 1.0f};

    SpriteRendererComponent() = default;
    SpriteRendererComponent(const SpriteRendererComponent &) = default;
    SpriteRendererComponent(const glm::vec4 &color) : Color(color)
    {
    }

    operator const glm::vec4 &() const
    {
        return Color;
    }
    operator glm::vec4 &()
    {
        return Color;
    }
};

struct CameraComponent
{
    SceneCamera Camera;
    bool Primary = true; // TODO: move to scene
    bool FixedAspectRatio = false;

    CameraComponent() = default;
    CameraComponent(const CameraComponent &) = default;
};

struct NativeScriptComponent
{
    ScriptableEntity *Instance = nullptr;

    ScriptableEntity *(*InstantiateScript)();
    void (*DestroyScript)(NativeScriptComponent *);

    template <typename T> void Bind()
    {
        InstantiateScript = []() { return static_cast<ScriptableEntity *>(new T()); };
        DestroyScript = [](NativeScriptComponent *nsc) {
            delete nsc->Instance;
            nsc->Instance = nullptr;
        };
    }
};

} // namespace gauri
