/**
 * File              : Renderer.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 22.02.2020
 * Last Modified Date: 25.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once
#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Engine {
  class Renderer
  {
  public:

    static void BeginScene(OrthographicCamera& camera); // TODO: add more params ;)
    static void EndScene();

    static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));

    inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); };
  private:
    struct SceneData
    {
      glm::mat4 ViewProjectionMatrix;

    };

    static SceneData* m_SceneData;
  };
};
