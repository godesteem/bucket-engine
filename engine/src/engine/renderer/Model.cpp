/**
 * File              : Model.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 01.03.2020
 * Last Modified Date: 01.03.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include "Model.h"
#include "Renderer.h"
#include "platform/opengl/OpenGLModel.h"

namespace Engine {
  Ref<Model> Model::Create(const std::string &objectFilePath, const std::string &shaderFilePath) {
    switch(Renderer::GetAPI()){
      case RendererAPI::API::None: BE_CORE_ASSERT(false, "RendererAPI::None is currently not supported ");
      case RendererAPI::API::OpenGL: return std::make_shared<OpenGLModel>(objectFilePath, shaderFilePath);
    }
    BE_CORE_ASSERT(false, "Unknown RendererAPI");
    return nullptr; 
    
  }

  Ref<Model> Model::Create(Ref<VertexBuffer>& vertexBuffer, Ref<IndexBuffer>& indexBuffer, const std::string& shaderFile) {
    switch(Renderer::GetAPI()){
      case RendererAPI::API::None: BE_CORE_ASSERT(false, "RendererAPI::None is currently not supported ");
      case RendererAPI::API::OpenGL: return std::make_shared<OpenGLModel>(vertexBuffer, indexBuffer, shaderFile);
    }
    BE_CORE_ASSERT(false, "Unknown RendererAPI");
    return nullptr;
  }
}
