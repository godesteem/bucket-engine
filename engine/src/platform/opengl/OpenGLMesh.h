/**
 * File              : OpenGLMesh.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 01.03.2020
 * Last Modified Date: 01.03.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once

#include "engine/renderer/Mesh.h"
#include "engine/renderer/Texture.h"

namespace Engine {
  class OpenGLMesh: public Mesh
  {
  friend Mesh;
  public:
    OpenGLMesh(const std::string &objectFilePath, const std::string &shaderFilePath="", const std::string &textureFilePath="");
    OpenGLMesh(Ref<VertexBuffer>& vertexBuffer, const Ref<IndexBuffer>& indexBuffer, const std::string& shaderFile);
    explicit OpenGLMesh(const Ref<OpenGLMesh>& mesh);
    virtual void Bind() const override;
    virtual void Unbind() const override;
    virtual void OnUpdate(Timestep ts) override;
    virtual void OnImGuiRender() override;
    virtual void SetVertexArraySize(uint32_t size) override;
    virtual void SetName(const std::string& name) override { m_Name = name; }
    virtual OpenGLMesh& operator=(const OpenGLMesh& msh);

  private:
    bool ExtractShaderFileContent(const std::string& shaderFilePath);
    static bool ReadObjFile(const std::string& filePath, std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, std::vector<glm::vec2> &uvs);
  private:
    std::string m_Name;
    Ref<VertexBuffer> m_VertexBuffer;
    Ref<VertexArray> m_VertexArray;
    ShaderLibrary m_ShaderLibrary;
    Ref<Texture2D> m_Texture;
    glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
    std::string m_ShaderFileContent;
  };
}
