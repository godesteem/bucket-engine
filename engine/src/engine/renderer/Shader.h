//
// Created by phil on 22.02.20.
//
#pragma once

#include "engine/Core.h"
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

namespace Engine {
  class Shader
  {
  public:
    virtual ~Shader() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual const std::string& GetName() const = 0;
    virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;
    virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) = 0;
    
    virtual void UploadUniformFloat(const std::string& name, float value) = 0;
    virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& values) = 0;
    virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& values) = 0;
    virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& values) = 0;

    virtual void UploadUniformInt(const std::string& name, int value) = 0;
    
    static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
    static Ref<Shader> Create(const std::string& filePath);
    virtual int GetUniformLocation(const std::string& name) const = 0;
    virtual int GetAttributeLocation(const std::string& name) const = 0;
    // virtual void UploadUniformBuffer() = 0;
  };

  class ShaderLibrary
  {
  public:
    void Add(const Ref<Shader>& shader);
    void Add(const std::string& name, const Ref<Shader>& shader);
    void Remove(const std::string& name);
    Ref<Shader> Load(const std::string& filePath);
    Ref<Shader> Load(const std::string& name, const std::string& filePath);
    
    Ref<Shader> Get(const std::string& name);

    bool Exists(const std::string& name) const;
  private:
    std::unordered_map<std::string, Ref<Shader>> m_Shaders;
  };
}
