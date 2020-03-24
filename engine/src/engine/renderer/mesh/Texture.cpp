#include "bepch.h"

#include "Texture.h"
#include "engine/renderer/Renderer.h"
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
