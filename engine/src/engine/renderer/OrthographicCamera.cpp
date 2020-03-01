/**
 * File              : OrthographicCamera.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 23.02.2020
 * Last Modified Date: 01.03.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include "bepch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

namespace Engine {

  Camera::Camera(glm::mat4 projection, glm::mat4 view)
    :m_ProjectionMatrix(projection), m_ViewMatrix(view)
  {
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
  };

  OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    :Camera(glm::ortho(left, right, bottom, top, -1.0f, 1.0f), glm::mat4(1.0f))
  {
  };
  void OrthographicCamera::RecalculateViewMatrix(){
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
                          glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.x), glm::vec3(1, 0, 0)) *
                          glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.y), glm::vec3(0, 1, 0));

    m_ViewMatrix = glm::inverse(transform);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
  };
  ThirdPersonCamera::ThirdPersonCamera(float left, float right, float bottom, float top)
  :Camera(glm::perspective(glm::radians(45.0f), (right-left)/(bottom-top), 0.1f, 100.0f), glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f))),
  MouseSensitivity(SENSITIFITY),
  MouseSpeed(SPEED),
  Zoom(ZOOM),
  WorldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
  m_Target(glm::vec3(0.0f)),
  m_Front(glm::vec3(0.0f, 0.0f, -1.0f)),
  Up(glm::vec3(0.0f, 1.0f, 0.0f))
  {
    m_Direction = glm::normalize(m_Position - m_Target);
    RecalculateViewMatrix();
  }
  ThirdPersonCamera::ThirdPersonCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
  : Camera(glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f), glm::mat4(1.0f)),
    Position(position),
    WorldUp(up),
    Yaw(yaw),
    Pitch(pitch),
    Front(glm::vec3(0.0f, 0.0f, -0.1f)),
    MouseSpeed(SPEED),
    MouseSensitivity(SENSITIFITY),
    Zoom(ZOOM)
  {
    RecalculateViewMatrix();
  };

  ThirdPersonCamera::ThirdPersonCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : Camera(glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f), glm::mat4(1.0f)),
    Front(glm::vec3(0.0f, 0.0f, -0.1f)),
    MouseSpeed(SPEED),
    MouseSensitivity(SENSITIFITY),
    Zoom(ZOOM),
    Position(glm::vec3(posX, posY, posZ)),
    WorldUp(glm::vec3(upX, upY, upZ)),
    Yaw(yaw),
    Pitch(pitch),
    m_Target(glm::vec3(0.0f)),
    m_Front(glm::vec3(0.0f))
    {
      m_Direction = glm::normalize(m_Position - m_Target);
      RecalculateViewMatrix();
    }

  void ThirdPersonCamera::RecalculateViewMatrix() {
    m_ViewMatrix = glm::inverse(glm::lookAt(m_Position, m_Position + m_Front, Up));
    //glm::inverse(transform);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    
    /*
    glm::mat4 tranform = glm::translate(glm::mat4(1.0f), m_Position) *
      glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

    //m_ViewMatrix = glm::inverse(tranform);
    m_ViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(.0f,0.0f,-3.0f));
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    
    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));

    m_ViewProjectionMatrix = glm::lookAt(Position, Position + Front, Up);

    //m_ViewProjectionMatrix = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    */
    /*
    glm::mat4 tranform = glm::translate(glm::mat4(1.0f), m_Position) *
      glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

    m_ViewMatrix = glm::inverse(tranform);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    */
  };
}
