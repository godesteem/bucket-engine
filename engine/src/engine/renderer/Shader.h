/**
 * File              : Shader.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 23.02.2020
 * Last Modified Date: 29.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
//
// Created by phil on 22.02.20.
//
#pragma once

#include "engine/Core.h"
#include <string>
#include <unordered_map>

namespace Engine {
  class Shader
  {
  public:
    virtual ~Shader() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual const std::string& GetName() const = 0;
    
    static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
    static Ref<Shader> Create(const std::string& filePath);
    // virtual void UploadUniformBuffer() = 0;
  };

  class ShaderLibrary
  {
  public:
    void Add(const Ref<Shader>& shader);
    void Add(const std::string& name, const Ref<Shader>& shader);
    Ref<Shader> Load(const std::string& filePath);
    Ref<Shader> Load(const std::string& name, const std::string& filePath);
    
    Ref<Shader> Get(const std::string& name);

    bool Exists(const std::string& name) const;
  private:
    std::unordered_map<std::string, Ref<Shader>> m_Shaders;
  };
}
