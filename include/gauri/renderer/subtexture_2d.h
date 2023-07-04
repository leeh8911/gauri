#pragma once

#include "glm/glm.hpp"

#include "gauri/renderer/texture.h"

namespace gauri
{
class SubTexture2D
{
  public:
    SubTexture2D(const Ref<Texture2D> &texture, const glm::vec2 &min, const glm::vec2 &max);

    const Ref<Texture2D> &GetTexture() const
    {
        return m_Texture;
    }

    const glm::vec2 *GetTexCoords()
    {
        return m_TexCoords;
    }

    static Ref<SubTexture2D> CreateFromCoords(const Ref<Texture2D> &texture, const glm::vec2 coords,
                                              const glm::vec2 spriteSize);

  private:
    Ref<Texture2D> m_Texture;

    glm::vec2 m_TexCoords[4];
};
} // namespace gauri
