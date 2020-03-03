/**
 * File              : OpenGLModel.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 01.03.2020
 * Last Modified Date: 01.03.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once

#include "engine/renderer/Model.h"
#include "engine/renderer/Texture.h"

namespace Engine {
  class OpenGLModel: public Model
  {
  friend Model;
  public:
    OpenGLModel(const std::string &objectFilePath, const std::string &shaderFilePath="", const std::string &textureFilePath="");
    OpenGLModel(Ref<VertexBuffer>& vertexBuffer, const Ref<IndexBuffer>& indexBuffer, const std::string& shaderFile);
    virtual void Bind() const override;
    virtual void Unbind() const override;
    virtual void OnUpdate(Timestep ts, Camera& camera) override;
    virtual void OnImGuiRender() override;
    virtual void SetVertexArraySize(uint32_t size) override;

  private:
    bool ReadObjFile(FILE* file, std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, std::vector<glm::vec2> &uvs);
  private:
    std::string m_Name;
    Ref<VertexBuffer> m_VertexBuffer;
    Ref<VertexBuffer> m_NormalBuffer;
    Ref<IndexBuffer> m_ElementsBuffer;
    Ref<VertexArray> m_VertexArray;
    ShaderLibrary m_ShaderLibrary;
    Ref<Shader> m_Shader;
    Ref<Texture2D> m_Texture;
    glm::vec3 m_Position = {1.0f, 1.0f, 1.0f};
#ifdef BE_DEBUG
    std::string m_ShaderFile;
#endif
  };
}
