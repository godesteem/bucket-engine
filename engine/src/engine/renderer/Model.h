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
#include <vector>
#include "Buffer.h"
#include "VertexArray.h"
#include "engine/core/Timestep.h"
#include "Shader.h"
#include "OrthographicCamera.h"

typedef ushort GLushort;

namespace Engine {

  class Model
  {
  public:
    virtual ~Model() = default;
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    virtual void OnUpdate(Timestep ts, Camera& camera) = 0;
    virtual void OnImGuiRender() = 0;

    static Ref<Model> Create(const std::string& filePath);
    //static Ref<Model> Create(const std::string& filePath);
  };
}
