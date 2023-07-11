#pragma once

#include <glm/glm.hpp>

namespace gauri
{
class Camera
{
  public:
    Camera(const glm::mat4 &projection) : m_Projection(projection)
    {
    }

    const glm::mat4 &GetProjection() const
    {
        return m_Projection;
    }

    // TODO:
  private:
    glm::mat4 m_Projection;
};
} // namespace gauri
