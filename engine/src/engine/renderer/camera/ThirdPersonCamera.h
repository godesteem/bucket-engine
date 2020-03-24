//
// Created by phil on 24.03.20.
//

#pragma once

#include "Camera.h"

namespace Engine {
  const float YAW = -90.0f;
  const float PITCH = 0.0f;
  const float SPEED = 2.5f;
  const float SENSITIFITY = 0.05f;
  const float ZOOM = 45.0f;

  class ThirdPersonCamera: public Camera
  {
  public:
    ThirdPersonCamera(float left, float right, float bottom, float top);

    virtual void OnUpdate(Timestep &ts) override;

    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

    float &GetYaw();
    float &GetPitch();

  private:
    virtual void RecalculateViewMatrix() override;

    glm::vec3 m_Target;
    glm::vec3 m_Front;
    glm::vec3 m_Direction;
    glm::vec3 Position, Front, Up, Right, WorldUp;
  public:
    float Yaw, Pitch, MouseSpeed, MouseSensitivity, Zoom;

  };
}