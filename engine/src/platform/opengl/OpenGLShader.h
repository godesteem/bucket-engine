/**
 * File              : OpenGLShader.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 25.02.2020
 * Last Modified Date: 29.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once

#include "engine/renderer/Shader.h"
#include <glm/glm.hpp>

//TODO: #include <glad/glad.h>
typedef int GLint;
typedef unsigned int GLenum;

#include <unordered_map>

namespace Engine {
  class OpenGLShader: public Shader
  {
  public:
    OpenGLShader(const std::string& filePath);
    OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
    virtual ~OpenGLShader();

    virtual void Bind() const override;
    virtual void Unbind() const override;
    
    void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
    void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
    
    void UploadUniformFloat(const std::string& name, float value);
    void UploadUniformFloat2(const std::string& name, const glm::vec2& values);
    void UploadUniformFloat3(const std::string& name, const glm::vec3& values);
    void UploadUniformFloat4(const std::string& name, const glm::vec4& values);

    void UploadUniformInt(const std::string& name, int value);
    /*
    void UploadUniformInt2(const std::string& name, const glm::vec2& values);
    void UploadUniformInt3(const std::string& name, const glm::vec3& values);
    void UploadUniformInt4(const std::string& name, const glm::vec4& values);
    */
  private:
    void Compile(std::unordered_map<GLenum, std::string>& shaderSources);
    std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
    std::string ReadFile(const std::string& filePath);
    GLint GetUniformLocation(const std::string& name) const;
  private:
    uint32_t m_RendererID;
    mutable std::unordered_map<std::string, GLint> m_UniformLocationCache;

  };
}
