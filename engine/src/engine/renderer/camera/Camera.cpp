//
// Created by phil on 24.03.20.
//

#include "Camera.h"

namespace Engine {

  Camera::CameraStack* Camera::camStack = new Camera::CameraStack();
  Camera::Camera(glm::mat4 projection, glm::mat4 view)
      : m_ProjectionMatrix(projection), m_ViewMatrix(view),
        m_Target(glm::vec3(0.0f)),
        m_Front(glm::vec3(0.0f, 0.0f, -1.0f)),
        m_Up(glm::vec3(0.0f, 1.0f, 0.0f)),
        m_ViewProjectionMatrix(m_ProjectionMatrix * m_ViewMatrix)
  {
    camStack->AddCamera(this);
  };
}