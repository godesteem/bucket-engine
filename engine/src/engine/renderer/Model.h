/**
 * File              : Model.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 01.03.2020
 * Last Modified Date: 01.03.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once
#include "engine/Core.h"
#include <glm/glm.hpp>
#include <utility>
#include <vector>
#include "Buffer.h"
#include "VertexArray.h"
#include "engine/core/Timestep.h"
#include "Shader.h"
#include "OrthographicCamera.h"

typedef ushort GLushort;

namespace Engine {
  struct ModelAttribute {
    std::string name;
    const VertexBuffer& buffer;

    ModelAttribute(std::string  n, const VertexBuffer& b)
    : name(std::move(n)), buffer(b)
    {}
  };
  class Model
  {
  public:
    virtual ~Model() = default;
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    virtual void OnUpdate(Timestep ts, Camera& camera) = 0;
    virtual void OnImGuiRender() = 0;

    std::vector<ModelAttribute> GetAttributes () { return m_Attributes; };
    inline void SetAttribute(const std::string& key, const VertexBuffer& buffer) {
      m_Attributes.emplace_back(key, buffer);
    };

    static Ref<Model> Create(const std::string &objectFilePath, const std::string &shaderFilePath);
    static Ref<Model> Create(Ref<VertexBuffer>& vertexBuffer, Ref<IndexBuffer>& indexBuffer, const std::string& shaderFile);
    virtual void SetVertexArraySize(uint32_t size) = 0;
    //static Ref<Model> Create(const std::string& filePath);
  protected:
    std::vector<ModelAttribute> m_Attributes;
  };
}
