/**
 * File              : Shader.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 23.02.2020
 * Last Modified Date: 29.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */

#include "bepch.h"
#include "Shader.h"
#include "Renderer.h"

#include "platform/opengl/OpenGLShader.h"

namespace Engine {
  Shader* Shader::Create(const std::string& filePath){
    switch(Renderer::GetAPI()){
      case RendererAPI::API::None: BE_CORE_ASSERT(false, "RendererAPI::None is currently not supported ");
      case RendererAPI::API::OpenGL: return new OpenGLShader(filePath);
    }
    BE_CORE_ASSERT(false, "Unknown RendererAPI");
    return nullptr; 
  }

  Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc){
    switch(Renderer::GetAPI()){
      case RendererAPI::API::None: BE_CORE_ASSERT(false, "RendererAPI::None is currently not supported ");
      case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
    }
    BE_CORE_ASSERT(false, "Unknown RendererAPI");
    return nullptr; 
  }
}
