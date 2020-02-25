/**
 * File              : Shader.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 23.02.2020
 * Last Modified Date: 25.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
//
// Created by phil on 22.02.20.
//
#pragma once

#include <string>

namespace Engine {
  class Shader
  {
  public:
    virtual ~Shader() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    
    static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
    // virtual void UploadUniformBuffer() = 0;
  };
}
