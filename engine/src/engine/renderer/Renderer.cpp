#include "bepch.h"
#include "Renderer.h"
#include "engine/Core.h"
#include "platform/opengl/OpenGLShader.h"


namespace Engine {
  Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

  void Renderer::Init(){
    RenderCommand::Init();
  }

  void Renderer::EndScene(){
  
  }

  void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform){
    shader->Bind();
    shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
    shader->UploadUniformMat4("u_Transform", transform);
    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
  }
 
};
