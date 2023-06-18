#pragma once

#include "gauri/core/timestep.h"
#include "gauri/event/event.h"
#include "gauri/renderer/orthographic_camera.h"

namespace gauri
{
class OrthographicCameraController
{
  public:
    OrthographicCameraController(float aspectRatio, bool rotation = false);

    void OnUpdate(Timestep ts);
    void OnEvent(Event &e);

    const OrthographicCamera &GetCamera() const
    {
        return m_Camera;
    }

    OrthographicCamera &GetCamera()
    {
        return m_Camera;
    }

  private:
    bool OnMouseScrolled(MouseScrolledEvent &e);
    bool OnWindowResized(WindowResizeEvent &e);

    float m_AspectRatio = 1.f;
    float m_ZoomLevel = 1.f;

    OrthographicCamera m_Camera;

    bool m_Rotation = false;
    glm::vec3 m_CameraPosition{0.0f, 0.0f, 0.0f};
    float m_CameraRotation = 0.0f;
    float m_CameraTranslationSpeed = 180.0f;
    float m_CameraRotationSpeed = 180.0f;
};

} // namespace gauri
