#pragma once
#include "RenderCommand.h"
#include "engine/renderer/camera/OrthographicCamera.h"
#include "Shader.h"

namespace Engine {
  class Renderer
  {
  public:
    static void Init();

    inline static void BeginScene(Camera& camera){
      m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }; // TODO: add more params ;)
    static void EndScene();

    static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));

    inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); };
  private:
    struct SceneData
    {
      glm::mat4 ViewProjectionMatrix;

    };

    static SceneData* m_SceneData;
  };
};
