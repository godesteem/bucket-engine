/**
 * File              : OpenGLModel.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 01.03.2020
 * Last Modified Date: 01.03.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once

#include "engine/renderer/Model.h"

namespace Engine {
  class OpenGLModel: public Model
  {
  public:
    OpenGLModel(const std::string& filePath);
    virtual void Bind() const override;
    virtual void Unbind() const override;
    virtual void OnUpdate(Timestep ts, Camera& camera) override;
    virtual void OnImGuiRender() override;
  };
}
