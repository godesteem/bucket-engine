/**
 * File              : OpenGLShader.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 25.02.2020
 * Last Modified Date: 01.03.2020
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
    OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
    virtual ~OpenGLShader();

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual const std::string& GetName() const override { return m_Name; };
    
    virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;
    virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) override;
    
    virtual void UploadUniformFloat(const std::string& name, float value) override;
    virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& values) override;
    virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& values) override;
    virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& values) override;

    virtual void UploadUniformInt(const std::string& name, int value) override;
    /*
    void UploadUniformInt2(const std::string& name, const glm::vec2& values);
    void UploadUniformInt3(const std::string& name, const glm::vec3& values);
    void UploadUniformInt4(const std::string& name, const glm::vec4& values);
    */
    virtual GLint GetUniformLocation(const std::string& name) const override;
  private:
    void Compile(std::unordered_map<GLenum, std::string>& shaderSources);
    std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
    std::string ReadFile(const std::string& filePath);
  private:
    uint32_t m_RendererID;
    std::string m_Name;
    mutable std::unordered_map<std::string, GLint> m_UniformLocationCache;

  };
}
