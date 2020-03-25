/**
 * File              : RendererAPI.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 23.02.2020
 * Last Modified Date: 29.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once
#include "engine/core/Core.h"
#include <glm/glm.hpp>
#include "VertexArray.h"

namespace Engine {
  
  class RendererAPI
  {
  public:
    enum class API
    {
      None = 0, OpenGL = 1,
    };
  public:
    virtual void Init() = 0;
    virtual void SetClearColor(const glm::vec4& color) = 0;
    virtual void Clear() = 0;

    virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;
    inline static API GetAPI() {return s_API;};
  private:
   static API s_API; 

  };

}
