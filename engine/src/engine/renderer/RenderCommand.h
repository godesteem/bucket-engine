/**
 * File              : RenderCommand.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 23.02.2020
 * Last Modified Date: 29.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once

#include "RendererAPI.h"


namespace Engine {

  class RenderCommand
  {
  public:
    inline static void Init(){
      s_RendererAPI->Init();
    }
    inline static void SetClearColor(const glm::vec4& color) {
      s_RendererAPI->SetClearColor(color);
    }

    inline static void Clear(){
      s_RendererAPI->Clear();
    }

    inline static void DrawIndexed(const Ref<VertexArray>& vertexArray){
      s_RendererAPI->DrawIndexed(vertexArray);
    }
  private:
    static RendererAPI* s_RendererAPI;
  };

}
