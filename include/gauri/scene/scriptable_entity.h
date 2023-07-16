#pragma once

#include "gauri/scene/entity.h"

namespace gauri
{
class ScriptableEntity
{
  public:
    template <typename T> T &GetComponent()
    {
        return m_Entity.GetComponent<T>();
    }

  private:
    Entity m_Entity;
    friend class Scene;
};
} // namespace gauri
