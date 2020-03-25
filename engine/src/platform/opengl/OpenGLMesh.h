#pragma once

#include "engine/renderer/mesh/Mesh.h"
#include "engine/renderer/mesh/Texture.h"

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
    virtual void SetPosition(glm::vec3& pos) override {m_Position = pos;};
    virtual void SetScale(float scale) override {m_Scale = scale;};
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
    float m_Scale = 1.0f;
  };
}
