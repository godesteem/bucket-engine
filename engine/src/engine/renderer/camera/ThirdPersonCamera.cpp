//
// Created by phil on 24.03.20.
//

#include "ThirdPersonCamera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <engine/core/io/KeyCodes.h>
#include <engine/core/io/Input.h>

namespace Engine {

  // TODO: Game settings
  static float WINDOW_WIDTH = 1280.0;
  static float WINDOW_HEIGHT = 720.0;
  float lastX = WINDOW_WIDTH / 2.0f;
  float lastY = WINDOW_HEIGHT / 2.0f;
  bool firstMouse = true;
  static std::pair<float, float> prev_position = {0.0f, 0.0f};
  const glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
  bool init = true;

  ThirdPersonCamera::ThirdPersonCamera(float left, float right, float bottom, float top)
      : Camera(glm::perspective(glm::radians(45.0f), (right-left)/(bottom-top), 0.1f, 100.0f), glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f))),
        MouseSensitivity(SENSITIFITY),
        MouseSpeed(SPEED),
        Zoom(ZOOM),
        Yaw(0.0f),
        Pitch(0.0f)
  {
    m_Direction = glm::normalize(m_Position - m_Target);
    RecalculateViewMatrix();
  }

  void ThirdPersonCamera::RecalculateViewMatrix() {
    /**
     *
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // Also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up    = glm::normalize(glm::cross(Right, Front));
     */
    glm::vec3 front;
    float distance = 10.0f;

    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    m_Front = glm::normalize(front) * distance;
    m_Right = glm::normalize(glm::cross(m_Front, WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
    m_Position = m_Target - m_Front;

    m_ViewMatrix = glm::lookAt(m_Position, m_Target, m_Up);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
  }


  void ThirdPersonCamera::OnUpdate(Timestep &tsr) {
    float ts = std::chrono::duration_cast<std::chrono::milliseconds>(tsr).count() / 1000.0f;
    {
      if (Input::IsKeyPressed(BE_KEY_LEFT)) {
        ProcessMouseMovement(m_Speed * 100.0f * ts, 0);
      } else if (Input::IsKeyPressed(BE_KEY_RIGHT)) {
        ProcessMouseMovement(-m_Speed * 100.0f * ts, 0);
      }
      if (Input::IsKeyPressed(BE_KEY_UP)) {
        ProcessMouseMovement(0, m_Speed * 100.0f * ts);
      } else if (Input::IsKeyPressed(BE_KEY_DOWN)) {
        ProcessMouseMovement(0, -m_Speed * 100.0f * ts);
      }
    }
    {
      float xpos = Engine::Input::GetMouseX();
      float ypos = Engine::Input::GetMouseY();

      if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
      }

      float xoffset = xpos - lastX;
      float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

      lastX = xpos;
      lastY = ypos;
      if (init || ((xpos != prev_position.first || ypos != prev_position.second) &&
                   Input::IsMouseButtonPressed(BE_MOUSE_BUTTON_2))) {
        ProcessMouseMovement(xoffset, yoffset, false);
        prev_position = {xpos, ypos};
        init = false;
      }
    }
    RecalculateViewMatrix();

  };

  void ThirdPersonCamera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    if (constrainPitch) {
      if (Pitch > 89.99f)
        Pitch = 89.99f;
      if (Pitch < -89.99f)
        Pitch = -89.99f;
    }
    RecalculateViewMatrix();
  }

}