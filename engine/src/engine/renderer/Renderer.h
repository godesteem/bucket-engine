/**
 * File              : Renderer.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 22.02.2020
 * Last Modified Date: 23.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once
#include "RenderCommand.h"

namespace Engine {
  class Renderer
  {
  public:

    static void BeginScene(); // TODO: add more params ;)
    static void EndScene();

    static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

    inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); };
  };
};
