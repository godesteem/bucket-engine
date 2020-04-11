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
    static bool ReadObjFile(const std::string& filePath, std::vector<Engine::Math::vec3> &vertices, std::vector<Engine::Math::vec3> &normals, std::vector<Engine::Math::vec2> &uvs);
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
