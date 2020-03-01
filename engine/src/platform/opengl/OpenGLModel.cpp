/**
 * File              : OpenGLModel.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 01.03.2020
 * Last Modified Date: 01.03.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include "bepch.h"
#include "OpenGLModel.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include "engine/renderer/Renderer.h"

namespace Engine {
  OpenGLModel::OpenGLModel(const std::string& filePath){
    BE_CHECK_FILE(filePath, ".obj");
    std::vector<glm::vec4> vertices;
    std::vector<glm::vec3> normals;
    std::vector<GLushort> elements;

    std::ifstream in(filePath, std::ios::in);
    if(!in){
      BE_CORE_ASSERT(false, "Cannot open model file");
    }
    std::string line;
    while(getline(in, line)){
      std::string type = line.substr(0,2);
      if(type == "v "){ // Vertex
        std::istringstream s(line.substr(2));
        glm::vec4 v; s >> v.x; s >> v.y; s >> v.z; v.w = 1.0f;
        vertices.push_back(v);
      } else if(type == "f "){ // Fragment
        std::istringstream s(line.substr(2));
        GLushort a, b, c;
        s >> a; s >> b; s >> c;
        a--; b--; c--;
        elements.push_back(a); elements.push_back(b); elements.push_back(c);
      } else if(line[0] == '#'){ // Comment line

      } else {
        BE_CORE_WARN("Unknown format \"{}\"", type);
      }
    }
    BE_CORE_ASSERT(vertices.size() > 0, "OpenGLModel::OpenGLModel() No data from file.");
    normals.resize(vertices.size(), glm::vec3(0.0f));
    for(int i = 0; i < elements.size(); ++i){
      GLushort ia = elements[i];
      GLushort ib = elements[i+1];
      GLushort ic = elements[i+2];
      glm::vec3 normal = glm::normalize(glm::cross(
        glm::vec3(vertices[ib]) - glm::vec3(vertices[ia]),
        glm::vec3(vertices[ic]) - glm::vec3(vertices[ia])
      ));
      normals[ia] = normals[ib] = normals[ic] = normal;
    }

    m_VertexArray.reset(VertexArray::Create());
    m_VertexBuffer.reset(Engine::VertexBuffer::Create(vertices, vertices.size() * 4));
    Engine::BufferLayout layout = {
        { Engine::ShaderDataType::Float4, "v" },
        { Engine::ShaderDataType::Float3, "v_normal" }
    };
    m_VertexBuffer->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(m_VertexBuffer);
    m_NormalBuffer.reset(VertexBuffer::Create(normals, normals.size() * 3));
    m_ElementsBuffer.reset(IndexBuffer::Create(elements, elements.size()));
    m_VertexArray->SetIndexBuffer(m_ElementsBuffer);

    auto last = filePath.find_last_of("/\\");
    last = last == std::string::npos ? 0 : last + 1;
    auto lastDot = filePath.rfind('.');

    auto count = lastDot == std::string::npos ? filePath.size() - last : lastDot - last;
    m_Name = filePath.substr(last, count);

    m_Shader = Shader::Create("/home/phil/work/private/games/bucket-engine/sandbox/assets/shaders/Suzanne.glsl");
    m_Shader->Bind();

    m_Shader->UploadUniformMat4("v", glm::mat4(1.0f));
    m_Shader->UploadUniformMat4("p", glm::mat4(1.0f));
    m_Shader->UploadUniformMat4("v_inv", glm::inverse(glm::mat4(1.0f)));
    m_Shader->UploadUniformFloat3("v_normal", glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position);
    m_Shader->UploadUniformMat3("m_inv_transp", glm::mat3(glm::transpose(glm::inverse(transform))));


  }

  void OpenGLModel::Bind() const {
    m_Shader->Bind();
    m_VertexBuffer->Bind();
    m_NormalBuffer->Bind();
    m_ElementsBuffer->Bind();

  }
  void OpenGLModel::Unbind() const {
  }

  void OpenGLModel::OnImGuiRender() {

  }

  void OpenGLModel::OnUpdate(Timestep ts, Camera& camera) {
    Bind();

    glm::mat4 world2camera = camera.GetViewMatrix();  // up
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position);

    glm::mat3 m_3x3_inv_transp = glm::transpose(glm::inverse(glm::mat3(transform)));
    m_Shader->UploadUniformMat3("m_inv_transp", m_3x3_inv_transp);



//    m_ElementsBuffer->Bind();
//    int size; glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
//    glDrawElements(GL_TRIANGLES, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
    m_ElementsBuffer->Bind();
//    int size;  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
//    glDrawElements(GL_TRIANGLES, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);

    Renderer::Submit(m_VertexArray, m_Shader, transform);
    glDisableVertexAttribArray(m_Shader->GetUniformLocation("v"));
    glDisableVertexAttribArray(m_Shader->GetUniformLocation("v_normal"));
  }
}
