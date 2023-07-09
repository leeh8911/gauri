#pragma once

#include <glm/glm.hpp>

namespace gauri
{
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
struct MeshComponent
{
    float Value;
    MeshComponent() = default;
};
} // namespace gauri
