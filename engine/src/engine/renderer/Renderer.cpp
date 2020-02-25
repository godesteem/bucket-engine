/**
 * File              : Renderer.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 22.02.2020
 * Last Modified Date: 25.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include "bepch.h"
#include "Renderer.h"
#include "engine/Core.h"
#include "platform/opengl/OpenGLShader.h"


namespace Engine {
  Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;
  void Renderer::BeginScene(OrthographicCamera& camera){
    m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix(); 
  }

  void Renderer::EndScene(){
  
  }

  void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform){
    shader->Bind();
    std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
    std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);
    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
  }
 
};
