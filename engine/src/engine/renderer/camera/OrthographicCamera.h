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
