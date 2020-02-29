/**
 * File              : OpenGLTexture.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 25.02.2020
 * Last Modified Date: 29.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */

#include "bepch.h"
#include "OpenGLTexture.h"

#include <stb_image/stb_image.h>

#include <glad/glad.h>


namespace Engine {
  OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
  : m_Path(path)
  {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    BE_CORE_ASSERT(data, "Failed to load image!");

    m_Width = width;
    m_Height = height;

    GLenum internalFormat = 0, dataFormat = 0;

    if(channels == 4){
      internalFormat = GL_RGBA8;
      dataFormat = GL_RGBA;
    }
    else if(channels == 3) {
      internalFormat = GL_RGB8;
      dataFormat = GL_RGB;
    }
    BE_CORE_ASSERT(internalFormat & dataFormat, "Format not supported.");

    glGenTextures(1, &m_RendererID);

    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);
  }
  OpenGLTexture2D::~OpenGLTexture2D(){
    glDeleteTextures(1, &m_RendererID);
  }

  void OpenGLTexture2D::Bind(uint32_t slot) const{
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
  }
}
