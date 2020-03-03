/**
 * File              : OpenGLRendererAPI.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 23.02.2020
 * Last Modified Date: 01.03.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */

#include "bepch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Engine {
  void OpenGLRendererAPI::Init(){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);
  }

  void OpenGLRendererAPI::SetClearColor(const glm::vec4& color){
    glClearColor(color.r, color.g, color.b, color.a);
  }

  void OpenGLRendererAPI::Clear(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray){
    if(vertexArray->GetIndexBuffer() != nullptr)
      glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    else{
      glDrawArrays(GL_TRIANGLES, 0, vertexArray->GetSize());
    }
  }
}
