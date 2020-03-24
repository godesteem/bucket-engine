/**
 * File              : OrthographicCamera.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 23.02.2020
 * Last Modified Date: 09.03.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once
#include "Camera.h"

namespace Engine {
  class OrthographicCamera: public Camera
  {
  public:
    virtual void OnUpdate(Timestep &ts) override;

  private:
    virtual void RecalculateViewMatrix() override;
  };

}
