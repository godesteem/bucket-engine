/**
 * File              : Shader.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 23.02.2020
 * Last Modified Date: 23.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
//
// Created by phil on 22.02.20.
//
#pragma once

#include <string>

#include <glm/glm.hpp>

namespace Engine {
  class Shader
  {
  public:
    Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
    ~Shader();

    void Bind() const;
    void Unbind() const;
    
    void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
  private:
    uint32_t m_RendererID;
  };
}
