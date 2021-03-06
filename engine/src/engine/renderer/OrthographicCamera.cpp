#include "bepch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <engine/KeyCodes.h>
#include <engine/Input.h>

namespace Engine {

  // TODO: Game settings
  static float WINDOW_WIDTH = 1280.0;
  static float WINDOW_HEIGHT = 720.0;
  float lastX = WINDOW_WIDTH / 2.0f;
  float lastY = WINDOW_HEIGHT / 2.0f;
  bool firstMouse = true;
  static std::pair<float, float> prev_position = {0.0f, 0.0f};
  bool init = true;

  Camera::CameraStack* Camera::camStack = new Camera::CameraStack();
  Camera::Camera(glm::mat4 projection, glm::mat4 view)
      : m_ProjectionMatrix(projection), m_ViewMatrix(view),
        m_ViewProjectionMatrix(m_ProjectionMatrix * m_ViewMatrix)
  {
    camStack->AddCamera(this);
  };

  void OrthographicCamera::RecalculateViewMatrix(){
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
                          glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.x), glm::vec3(1, 0, 0)) *
                          glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.y), glm::vec3(0, 1, 0));

    m_ViewMatrix = glm::inverse(transform);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
  };
  ThirdPersonCamera::ThirdPersonCamera(float left, float right, float bottom, float top)
  : Camera(glm::perspective(glm::radians(45.0f), (right-left)/(bottom-top), 0.1f, 100.0f), glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f))),
    MouseSensitivity(SENSITIFITY),
    MouseSpeed(SPEED),
    Zoom(ZOOM),
    WorldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
    m_Target(glm::vec3(0.0f)),
    m_Front(glm::vec3(0.0f, 0.0f, -1.0f)),
    Up(glm::vec3(0.0f, 1.0f, 0.0f)),
    Yaw(0.0f),
    Pitch(0.0f)
  {
    m_Direction = glm::normalize(m_Position - m_Target);
    RecalculateViewMatrix();
  }

  void ThirdPersonCamera::RecalculateViewMatrix() {
    m_Direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    m_Direction.y = sin(glm::radians(Pitch));
    m_Direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    m_Front = glm::normalize(m_Direction);
    // Also re-calculate the Right and Up vector
//    Right = glm::normalize(glm::cross(m_Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
//    Up    = glm::normalize(glm::cross(Right, m_Front));

    m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, Up);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
  }


  void ThirdPersonCamera::OnUpdate(Timestep& tsr) {
  const float ts = tsr.count();
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
      if (Input::IsKeyPressed(BE_KEY_W)) {
        m_Position += m_Speed * ts * m_Front;
      } else if (Input::IsKeyPressed(BE_KEY_S)) {
        m_Position -= m_Speed * ts * m_Front;
      }
      if (Input::IsKeyPressed(BE_KEY_A)) {
        m_Position += glm::normalize(glm::cross(m_Front, Up)) * (m_Speed * ts);
      } else if (Input::IsKeyPressed(BE_KEY_D)) {
        m_Position -= glm::normalize(glm::cross(m_Front, Up)) * (m_Speed * ts);
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
      if (Pitch > 90.0f)
        Pitch = 90.0f;
      if (Pitch < -90.0f)
        Pitch = -90.0f;
    }
    RecalculateViewMatrix();
  }

  float &ThirdPersonCamera::GetYaw() {
    return Yaw;
  }

  float &ThirdPersonCamera::GetPitch() {
    return Pitch;
  };
}
