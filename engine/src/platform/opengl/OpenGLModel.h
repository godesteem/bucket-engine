/**
 * File              : OpenGLModel.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 01.03.2020
 * Last Modified Date: 01.03.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once

#include "engine/renderer/Model.h"

namespace Engine {
  class OpenGLModel: public Model
  {
  friend Model;
  public:
    OpenGLModel(const std::string &objectFilePath, const std::string &shaderFilePath);
    OpenGLModel(Ref<VertexBuffer>& vertexBuffer, const Ref<IndexBuffer>& indexBuffer, const std::string& shaderFile);
    virtual void Bind() const override;
    virtual void Unbind() const override;
    virtual void OnUpdate(Timestep ts, Camera& camera) override;
    virtual void OnImGuiRender() override;
    virtual void SetVertexArraySize(uint32_t size) override;

  private:
    std::string m_Name;
    Ref<VertexBuffer> m_VertexBuffer;
    Ref<VertexBuffer> m_NormalBuffer;
    Ref<IndexBuffer> m_ElementsBuffer;
    Ref<VertexArray> m_VertexArray;
    ShaderLibrary m_ShaderLibrary;
    Ref<Shader> m_Shader;
    glm::vec3 m_Position = {1.0f, 1.0f, 1.0f};
  };
}
