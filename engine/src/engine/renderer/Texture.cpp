/**
 * File              : Texture.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 25.02.2020
 * Last Modified Date: 25.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include "bepch.h"

#include "Texture.h"
#include "Renderer.h"
#include "platform/opengl/OpenGLTexture.h"

namespace Engine {
  Ref<Texture2D> Texture2D::Create(const std::string& path){
    std::string filePath = CONSTRUCT_FILE_PATH(path);
    switch(Renderer::GetAPI()){
      case RendererAPI::API::None: BE_CORE_ASSERT(false, "RendererAPI::None is currently not supported ");
      case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(filePath);
    }
    BE_CORE_ASSERT(false, "Unknown RendererAPI");
    return nullptr; 

  }
}
