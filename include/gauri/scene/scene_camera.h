#pragma once

#include "gauri/renderer/camera.h"

namespace gauri
{
class SceneCamera : public Camera
{
  public:
    SceneCamera();
    ~SceneCamera() override = default;

    void SetOrthographic(float size, float nearClip, float farClip);

    void SetViewportSize(uint32_t width, uint32_t height);

    float GetOrthographicSize() const
    {
        return m_OrthographicSize;
    }
    void SetOrthographicSize(float size)
    {
        m_OrthographicSize = size;
        RecalculateProjection();
    }

  private:
    float m_OrthographicSize = 10.0f;
    float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;

    float m_AspectRatio = 0.0f;

    void RecalculateProjection();
};
} // namespace gauri
