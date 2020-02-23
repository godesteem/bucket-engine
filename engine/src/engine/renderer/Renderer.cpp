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
  void Renderer::BeginScene(){
     
  }

  void Renderer::EndScene(){
  
  }

  void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray){
    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
  }
 
};
