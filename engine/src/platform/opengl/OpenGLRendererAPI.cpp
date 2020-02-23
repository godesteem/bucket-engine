/**
 * File              : OpenGLRendererAPI.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 23.02.2020
 * Last Modified Date: 23.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */

#include "bepch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Engine {
    void OpenGLRendererAPI::SetClearColor(const glm::vec4& color){
      glClearColor(color.r, color.g, color.b, color.a);
    }
    void OpenGLRendererAPI::Clear(){
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray){
      glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

}
