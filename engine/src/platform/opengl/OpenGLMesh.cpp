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
    if(!shaderFilePath.empty())
      BE_CHECK_FILE(shaderFilePath, ".glsl");
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;
    std::vector<GLushort> elements;
    std::vector<std::string> attributes;

    FILE * file = fopen(objectFilePath.c_str(), "r");
    if( file == nullptr){
      printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
      getchar();
    }
    ReadObjFile(file, vertices, normals, uvs);
    fclose(file);

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
    m_Shader = Shader::Create(shaderFilePath.empty() ? DEFAULT_SHADER : shaderFilePath);
#ifdef BE_DEBUG

    std::ifstream shaderFile(shaderFilePath.empty() ? DEFAULT_SHADER.c_str() : shaderFilePath.c_str());
    BE_CORE_ASSERT(!shaderFile.is_open(), "Impossible to open shader file!");

    std::string line;
    while ( getline (shaderFile,line) ) {
      m_ShaderFile += line;
      m_ShaderFile += "\n";
    }

    shaderFile.close();
#endif
    if(!textureFilePath.empty())
      m_Texture = Texture2D::Create(textureFilePath);
  }

  OpenGLMesh::OpenGLMesh(Ref<VertexBuffer>& vertexBuffer, const Ref<IndexBuffer>& indexBuffer, const std::string& shaderFile){
    m_VertexArray->AddVertexBuffer(vertexBuffer);
    m_VertexArray->SetIndexBuffer(indexBuffer);
    m_Shader = Shader::Create(shaderFile);
    m_Shader->Bind();
  }
  void OpenGLMesh::Bind() const {
    if(m_Texture != nullptr) m_Texture->Bind();
  }
  void OpenGLMesh::Unbind() const {
  }

  void OpenGLMesh::OnImGuiRender() {
    ImGui::Begin(m_Name.c_str());
    ImGui::Text("Object Position (%d, %d, %d)", (int)m_Position.x, (int)m_Position.y, (int)m_Position.z);
    ImGui::PushItemWidth(120);
    ImGui::SliderFloat(std::string(m_Name + "ModelX").c_str(), &m_Position.x, -100.0f, 100.0f, "%.2f");
    ImGui::SameLine(160);
    ImGui::SliderFloat(std::string(m_Name + "ModelY").c_str(), &m_Position.y, -100.0f, 100.0f, "%.2f");
    ImGui::SameLine(320);
    ImGui::SliderFloat(std::string(m_Name + "ModelZ").c_str(), &m_Position.z, -100.0f, 100.0f, "%.2f");
    ImGui::PopItemWidth();
//    ImGui::TextWrapped("%s", m_ShaderFile.c_str());
    ImGui::InputTextMultiline(std::string(m_Name + "Shader").c_str(), &m_ShaderFile[0], 10000);
    if(ImGui::Button("Save Shader", {80, 0})){
      std::string newShaderFileName = "/home/phil/work/private/games/bucket-engine/sandbox/assets/shaders/" + m_Name + ".glsl";
      std::ofstream out(newShaderFileName.c_str());
      out << m_ShaderFile.c_str();
      out.close();
      m_Shader = Shader::Create(newShaderFileName);
    }
    ImGui::End();
  }

  void OpenGLMesh::OnUpdate(Timestep ts, Camera& camera) {
    Bind();
    glm::mat4 model(1.0f);
    m_Shader->Bind();
    m_Shader->UploadUniformMat4("model", model);
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position);
    Renderer::Submit(m_VertexArray, m_Shader, transform);
    Unbind();
  }

  void OpenGLMesh::SetVertexArraySize(uint32_t size) {
    m_VertexArray->SetSize(size);
  }

  bool OpenGLMesh::ReadObjFile(FILE* file, std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, std::vector<glm::vec2> &uvs) {
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;

    bool hasUVs = true;


    while( true ){
      char lineHeader[128];
      // read the first word of the line
      int res = fscanf(file, "%s", lineHeader);
      if (res == EOF)
        break; // EOF = End Of File. Quit the loop.

      // else : parse lineHeader

      if ( strcmp( lineHeader, "v" ) == 0 ){
        glm::vec3 vertex;
        fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
        temp_vertices.push_back(vertex);
      }else if ( strcmp( lineHeader, "vt" ) == 0 ){
        glm::vec2 uv;
        fscanf(file, "%f %f\n", &uv.x, &uv.y );
        uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
        temp_uvs.push_back(uv);
      }else if ( strcmp( lineHeader, "vn" ) == 0 ){
        glm::vec3 normal;
        fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
        temp_normals.push_back(normal);
      }else if ( strcmp( lineHeader, "f" ) == 0 ){
        std::string vertex1, vertex2, vertex3;
        unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
        int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
        if (matches != 9){
          printf("File can't be read by our simple parser :-( Try exporting with other options\n");
          fclose(file);
          return false;
        }
        vertexIndices.push_back(vertexIndex[0]);
        vertexIndices.push_back(vertexIndex[1]);
        vertexIndices.push_back(vertexIndex[2]);
        if(hasUVs) {
          uvIndices.push_back(uvIndex[0]);
          uvIndices.push_back(uvIndex[1]);
          uvIndices.push_back(uvIndex[2]);
        }
        normalIndices.push_back(normalIndex[0]);
        normalIndices.push_back(normalIndex[1]);
        normalIndices.push_back(normalIndex[2]);
      }else{
        // Probably a comment, eat up the rest of the line
        char stupidBuffer[1000];
        fgets(stupidBuffer, 1000, file);
      }

    }

    // For each vertex of each triangle
    for( unsigned int i=0; i<vertexIndices.size(); i++ ){
      if(!temp_vertices.empty()) {
        unsigned int vertexIndex = vertexIndices[i];
        glm::vec3 vertex = temp_vertices[vertexIndex - 1];
        vertices.push_back(vertex);
      }
      if(!temp_uvs.empty()) {
        unsigned int uvIndex = uvIndices[i];
        glm::vec2 uv = temp_uvs[uvIndex - 1];
        uvs.push_back(uv);
      }
      if(!temp_normals.empty()) {
        unsigned int normalIndex = normalIndices[i];
        glm::vec3 normal = temp_normals[normalIndex - 1];
        normals.push_back(normal);
      }
    }
    return true;
  }

}
