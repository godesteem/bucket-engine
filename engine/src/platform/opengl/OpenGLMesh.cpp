#include "bepch.h"
#include "OpenGLMesh.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <imgui/imgui.h>
#include "engine/renderer/Renderer.h"

/*
 * TODO: clean up unnecessary/dead code
 */


namespace Engine {
  std::string DEFAULT_SHADER = CONSTRUCT_FILE_PATH("sandbox/assets/shaders/Example.glsl");

  OpenGLMesh::OpenGLMesh(const std::string &objectFilePath, const std::string &shaderFilePath, const std::string &textureFilePath) {
    BE_CHECK_FILE(objectFilePath, ".obj");
    if(!shaderFilePath.empty()){
      BE_CHECK_FILE(shaderFilePath, ".glsl");
    }
    std::vector<Engine::Math::vec3> vertices;
    std::vector<Engine::Math::vec3> normals;
    std::vector<Engine::Math::vec2> textures;
    std::vector<ObjFile::face> faces;

    size_t VertexIndex  = 0;
    size_t NormalIndex  = 1;
    size_t TextureIndex = 2;

    /*
     * TODO:
     *  - also receive faces back
     *  - create VertexBuffer + IndexBuffer combinations for vertices, normals, textures using faces
     *  - combine VertexBuffer + IndexBuffer combinations in VertexArrays including their layout
     *  - attach all generated VertexArrays to the Mesh
     */
    ReadObjFile(objectFilePath, vertices, normals, textures, faces);
    bool hasNormals = normals.size() > 1;
    bool hasTextures = textures.size() > 1;
    Ref<VertexBuffer> vertexBuffer;
    m_VertexArray.reset(VertexArray::Create());
    m_VertexArray->Bind();

    Engine::BufferLayout vertexLayout;
    if(!hasTextures || !hasNormals){
      vertexLayout = {
          {Engine::ShaderDataType::Float3, "position"},
      };
      vertexBuffer.reset(Engine::VertexBuffer::Create(vertices, vertices.size() * sizeof(Engine::Math::vec3)));
    }
    else if(hasTextures && hasNormals) {
      vertexBuffer.reset(Engine::VertexBuffer::Create(
          vertices, vertices.size() * sizeof(Engine::Math::vec3),
          normals, normals.size() * sizeof(Engine::Math::vec3),
          textures, textures.size() * sizeof(Engine::Math::vec2)));
      vertexLayout = {
          {Engine::ShaderDataType::Float3, "position", false, VertexIndex},
          {Engine::ShaderDataType::Float3, "normals", false, NormalIndex},
          {Engine::ShaderDataType::Float2, "vertexUV", false, TextureIndex}
      };
    }

    vertexBuffer->SetLayout(vertexLayout);
    m_VertexArray->AddVertexBuffer(vertexBuffer);

    std::vector<unsigned short> vertexFaces;
    std::vector<unsigned short> normalFaces;
    std::vector<unsigned short> textureFaces;
    size_t i = 0;
    for(auto face : faces){
      vertexFaces.insert(vertexFaces.begin() + i, face.p1.vertex);
      vertexFaces.insert(vertexFaces.begin() + i + 1, face.p2.vertex);
      vertexFaces.insert(vertexFaces.begin() + i + 2, face.p3.vertex);

      if(hasTextures){
        textureFaces.insert(textureFaces.begin() + i, face.p1.texture);
        textureFaces.insert(textureFaces.begin() + i + 1, face.p2.texture);
        textureFaces.insert(textureFaces.begin() + i + 2, face.p3.texture);
      }
      if(hasNormals){
        normalFaces.insert(normalFaces.begin() + i, face.p1.normal);
        normalFaces.insert(normalFaces.begin() + i + 1, face.p2.normal);
        normalFaces.insert(normalFaces.begin() + i + 2, face.p3.normal);
      }
      i += 3;
    }

    Ref<IndexBuffer> indexBuffer;
    indexBuffer.reset(IndexBuffer::Create(vertexFaces, vertexFaces.size()));
    m_VertexArray->SetIndexBuffer(indexBuffer);

    if(!normalFaces.empty()){
      indexBuffer.reset(IndexBuffer::Create(normalFaces, normalFaces.size()));
      m_VertexArray->SetIndexBuffer(indexBuffer);
    }
    if(!textureFaces.empty()){
      indexBuffer.reset(IndexBuffer::Create(textureFaces, textureFaces.size()));
      m_VertexArray->SetIndexBuffer(indexBuffer);
    }



    m_VertexArray->Unbind();

    // extract object name
    auto last = objectFilePath.find_last_of("/\\");
    last = last == std::string::npos ? 0 : last + 1;
    auto lastDot = objectFilePath.rfind('.');
    auto count = lastDot == std::string::npos ? objectFilePath.size() - last : lastDot - last;
    m_Name = objectFilePath.substr(last, count);

    // TODO: drop this.
    SetVertexArraySize(vertexFaces.size());

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

    auto last = shaderFile.find_last_of("/\\");
    last = last == std::string::npos ? 0 : last + 1;
    auto lastDot = shaderFile.rfind('.');

    auto count = lastDot == std::string::npos ? shaderFile.size() - last : lastDot - last;
    m_Name = shaderFile.substr(last, count);
    ExtractShaderFileContent(shaderFile);
  }
  void OpenGLMesh::Bind() const {
    if(m_Texture != nullptr) m_Texture->Bind();
  }
  void OpenGLMesh::Unbind() const {
  }

  OpenGLMesh& OpenGLMesh::operator=(const OpenGLMesh& ms){
    m_Name = ms.m_Name;
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
        std::string newShaderFileName = "sandbox/assets/shaders/" + m_Name + ".glsl";
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

  bool OpenGLMesh::ReadObjFile(const std::string& filePath, std::vector<Engine::Math::vec3> &vertices, std::vector<Engine::Math::vec3> &normals, std::vector<Engine::Math::vec2> &uvs, std::vector<ObjFile::face> &faces) {
    /**
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
    uvs = file.GetTextureUVs();
    normals = file.GetNormals();
    faces = file.GetFaces();
    return true;
  }

  OpenGLMesh::OpenGLMesh(const Ref<OpenGLMesh> &ms){
    m_Name = ms->m_Name;
    m_VertexArray = ms->m_VertexArray;
    m_ShaderLibrary = ms->m_ShaderLibrary;
    m_Texture = ms->m_Texture;
    m_Position = ms->m_Position;
    m_ShaderFileContent = ms->m_ShaderFileContent;
  }

  bool OpenGLMesh::ExtractShaderFileContent(const std::string& shaderFilePath) {
    const std::string absoluteShaderFilePath = CONSTRUCT_FILE_PATH(shaderFilePath);
    std::ifstream shaderFile(shaderFilePath.empty() ? CONSTRUCT_FILE_PATH(DEFAULT_SHADER).c_str() : absoluteShaderFilePath.c_str());
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
