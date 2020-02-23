/**
 * File              : Renderer.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 22.02.2020
 * Last Modified Date: 23.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include "bepch.h"
#include "Renderer.h"


namespace Engine {
  Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;
  void Renderer::BeginScene(OrthographicCamera& camera){
    m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix(); 
  }

  void Renderer::EndScene(){
  
  }

  void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader){
    shader->Bind();
    shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);

    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
  }
 
};
