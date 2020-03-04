/**
 * File              : Mesh.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 01.03.2020
 * Last Modified Date: 01.03.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include "Mesh.h"
#include "Renderer.h"
#include "platform/opengl/OpenGLMesh.h"

namespace Engine {
  Ref<Mesh> Mesh::Create(const std::string &objectFilePath, const std::string &shaderFilePath) {
    switch(Renderer::GetAPI()){
      case RendererAPI::API::None: BE_CORE_ASSERT(false, "RendererAPI::None is currently not supported ");
      case RendererAPI::API::OpenGL: return std::make_shared<OpenGLMesh>(objectFilePath, shaderFilePath);
    }
    BE_CORE_ASSERT(false, "Unknown RendererAPI");
    return nullptr; 
    
  }

  Ref<Mesh> Mesh::Create(Ref<VertexBuffer>& vertexBuffer, Ref<IndexBuffer>& indexBuffer, const std::string& shaderFile) {
    switch(Renderer::GetAPI()){
      case RendererAPI::API::None: BE_CORE_ASSERT(false, "RendererAPI::None is currently not supported ");
      case RendererAPI::API::OpenGL: return std::make_shared<OpenGLMesh>(vertexBuffer, indexBuffer, shaderFile);
    }
    BE_CORE_ASSERT(false, "Unknown RendererAPI");
    return nullptr;
  }
}
