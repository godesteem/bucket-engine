/**
 * File              : Renderer.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 22.02.2020
 * Last Modified Date: 22.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once

namespace Engine {
  enum class RendererAPI
  {
    None = 0, OpenGL = 1,
  };

  class Renderer
  {
  public:
    inline static RendererAPI GetAPI() { return s_RendererAPI; };
  private:
    static RendererAPI s_RendererAPI;
  };
};
