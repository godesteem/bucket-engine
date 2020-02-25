/**
 * File              : OpenGLTexture.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 25.02.2020
 * Last Modified Date: 25.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once

#include "engine/renderer/Texture.h"

namespace Engine {

  class OpenGLTexture2D: public Texture2D
  {
  public:
    OpenGLTexture2D(const std::string& path);
    virtual ~OpenGLTexture2D();

    virtual uint32_t GetWidth() const override { return m_Width; };
    virtual uint32_t GetHeight() const override { return m_Height; };

    virtual void Bind(uint32_t slot = 0) const override;
  
  private:
    std::string m_Path;
    uint32_t m_Width, m_Height;
    uint32_t m_RendererID;

  };

}
