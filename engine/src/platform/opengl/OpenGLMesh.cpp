/**
 * File              : OpenGLMesh.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 01.03.2020
 * Last Modified Date: 01.03.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include "bepch.h"
#include "OpenGLMesh.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <imgui/imgui.h>
#include "engine/renderer/Renderer.h"

std::string DEFAULT_SHADER = "/home/phil/work/private/games/bucket-engine/sandbox/assets/shaders/Example.glsl";

namespace Engine {
  int shaderCount = 0;
  OpenGLMesh::OpenGLMesh(const std::string &objectFilePath, const std::string &shaderFilePath, const std::string &textureFilePath) {
    BE_CHECK_FILE(objectFilePath, ".obj");
    if(!shaderFilePath.empty()){
      BE_CHECK_FILE(shaderFilePath, ".glsl");
    }
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;

    ReadObjFile(objectFilePath, vertices, normals, uvs);

    m_VertexArray.reset(VertexArray::Create());
    if(!vertices.empty()) {
      m_VertexBuffer.reset(Engine::VertexBuffer::Create(vertices, vertices.size() * sizeof(glm::vec3)));
      Engine::BufferLayout vertexLayout = {
          {Engine::ShaderDataType::Float3, "position"}
      };
      m_VertexBuffer->SetLayout(vertexLayout);
      m_VertexArray->AddVertexBuffer(m_VertexBuffer);
    }
    if(!uvs.empty()) {
      m_VertexBuffer.reset(Engine::VertexBuffer::Create(uvs, vertices.size() * sizeof(glm::vec2)));
      Engine::BufferLayout vertexLayout = {
          {Engine::ShaderDataType::Float2, "vertexUV"}
      };
      m_VertexBuffer->SetLayout(vertexLayout);
      m_VertexArray->AddVertexBuffer(m_VertexBuffer);
    }
    auto last = objectFilePath.find_last_of("/\\");
    last = last == std::string::npos ? 0 : last + 1;
    auto lastDot = objectFilePath.rfind('.');

    auto count = lastDot == std::string::npos ? objectFilePath.size() - last : lastDot - last;
    m_Name = objectFilePath.substr(last, count);
    SetVertexArraySize(vertices.size());
    m_ShaderLibrary.Load("Main", shaderFilePath.empty() ? DEFAULT_SHADER : shaderFilePath);

    ExtractShaderFileContent(shaderFilePath);
    if(!textureFilePath.empty())
      m_Texture = Texture2D::Create(textureFilePath);
  }

  OpenGLMesh::OpenGLMesh(Ref<VertexBuffer>& vertexBuffer, const Ref<IndexBuffer>& indexBuffer, const std::string& shaderFile){
    m_VertexArray.reset(VertexArray::Create());
    m_VertexArray->AddVertexBuffer(vertexBuffer);
    m_VertexArray->SetIndexBuffer(indexBuffer);
    m_ShaderLibrary.Load("Main", shaderFile);
    ExtractShaderFileContent(shaderFile);
  }
  void OpenGLMesh::Bind() const {
    if(m_Texture != nullptr) m_Texture->Bind();
  }
  void OpenGLMesh::Unbind() const {
  }

  OpenGLMesh& OpenGLMesh::operator=(const OpenGLMesh& ms){
    m_Name = ms.m_Name;
    m_VertexBuffer = ms.m_VertexBuffer;
    m_VertexArray = ms.m_VertexArray;
    m_ShaderLibrary = ms.m_ShaderLibrary;
    m_Texture = ms.m_Texture;
    m_Position = ms.m_Position;
    m_ShaderFileContent = ms.m_ShaderFileContent;

    return *this;
  }

  void OpenGLMesh::OnImGuiRender() {
    if(ImGui::BeginTabItem(m_Name.c_str())) {
      ImGui::Text("Object Position (%d, %d, %d)", (int) m_Position.x, (int) m_Position.y, (int) m_Position.z);
      ImGui::PushItemWidth(120);
      ImGui::SliderFloat(std::string(m_Name + "ModelX").c_str(), &m_Position.x, -100.0f, 100.0f, "%.2f");
      ImGui::SameLine(160);
      ImGui::SliderFloat(std::string(m_Name + "ModelY").c_str(), &m_Position.y, -100.0f, 100.0f, "%.2f");
      ImGui::SameLine(320);
      ImGui::SliderFloat(std::string(m_Name + "ModelZ").c_str(), &m_Position.z, -100.0f, 100.0f, "%.2f");
      ImGui::PopItemWidth();
//    ImGui::TextWrapped("%s", m_ShaderFileContent.c_str());
      ImGui::InputTextMultiline(std::string(m_Name + "Shader").c_str(), &m_ShaderFileContent[0], 10000);
      if (ImGui::Button("Save Shader", {80, 0})) {
        std::string newShaderFileName =
            "/home/phil/work/private/games/bucket-engine/sandbox/assets/shaders/" + m_Name + ".glsl";
        std::ofstream out(newShaderFileName.c_str());
        out << m_ShaderFileContent.c_str();
        out.close();
        m_ShaderLibrary.Load("Main", newShaderFileName);
      }
      ImGui::EndTabItem();
    }
  }

  void OpenGLMesh::OnUpdate(Timestep ts) {
    Bind();
    glm::mat4 model(1.0f);
    auto shader = m_ShaderLibrary.Get("Main");
    shader->Bind();
    shader->UploadUniformMat4("model", model);
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position);
    Renderer::Submit(m_VertexArray, shader, transform);
    Unbind();
  }

  void OpenGLMesh::SetVertexArraySize(uint32_t size) {
    m_VertexArray->SetSize(size);
  }

  bool OpenGLMesh::ReadObjFile(const std::string& filePath, std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, std::vector<glm::vec2> &uvs) {
    /*
     * Loads a .obj file with following layout
     * vertices    : v %f %f %f
     * uvs         : vt %f %f
     * normals     : vn %f %f %f
     * figure faces:
     * syntax: <v>/<vt>/<vn> || <v> || <v>//<vn>
     * f %d %d %d
     * f %d//%d %d//%d %d//%d
     * f %d/%d/%d %d/%d/%d %d/%d/%d
     */

    ObjFile file(filePath);
    vertices = file.GetVertices();
    uvs = file.GetUVs();
    normals = file.GetNormals();
    return true;
  }

  OpenGLMesh::OpenGLMesh(const Ref<OpenGLMesh> &ms){
    m_Name = ms->m_Name;
    m_VertexBuffer = ms->m_VertexBuffer;
    m_VertexArray = ms->m_VertexArray;
    m_ShaderLibrary = ms->m_ShaderLibrary;
    m_Texture = ms->m_Texture;
    m_Position = ms->m_Position;
    m_ShaderFileContent = ms->m_ShaderFileContent;
  }

  bool OpenGLMesh::ExtractShaderFileContent(const std::string& shaderFilePath) {
    std::ifstream shaderFile(shaderFilePath.empty() ? DEFAULT_SHADER.c_str() : shaderFilePath.c_str());
    BE_CORE_ASSERT(shaderFile.is_open(), "Impossible to open shader file!");
    std::string line;
    while ( getline (shaderFile,line) ) {
      m_ShaderFileContent += line;
      m_ShaderFileContent += "\n";
    }
    shaderFile.close();
    return true;
  }

}
