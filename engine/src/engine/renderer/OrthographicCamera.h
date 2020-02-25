/**
 * File              : OrthographicCamera.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 23.02.2020
 * Last Modified Date: 25.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once

#include <glm/glm.hpp>

namespace Engine {
  const float YAW = -90.0f;
  const float PITCH = 0.0f;
  const float SPEED = 2.5f;
  const float SENSITIFITY = 0.1f;
  const float ZOOM = 45.0f;
  
  class Camera
  {
  public:
    Camera(float left, float right, float bottom, float top);
    void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix();};
    void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix();};

    glm::vec3& GetPosition() {return m_Position; };
    float GetRotation() const { return m_Rotation; };
    
    const glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; };
    const glm::mat4& GetViewMatrix() { return m_ViewMatrix; };
    const glm::mat4& GetViewProjectionMatrix() { return m_ViewProjectionMatrix; };

    virtual void RecalculateViewMatrix() = 0;
  protected:
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ViewProjectionMatrix;

    glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
    float m_Rotation = 0.0f; 
  };
  
  class OrthographicCamera: public Camera
  {
  public:
    OrthographicCamera(float left, float right, float bottom, float top);

  private:
    virtual void RecalculateViewMatrix() override;
  };
  
  class ThirdPersonCamera: public Camera
  {
  public:
    ThirdPersonCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
    ThirdPersonCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

    inline void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
    {
      xoffset *= MouseSensitivity;
      yoffset *= MouseSensitivity;

      Yaw   += xoffset;
      Pitch += yoffset;

      if (constrainPitch)
      {
        if (Pitch > 89.0f)
          Pitch = 89.0f;
        if (Pitch < -89.0f)
          Pitch = -89.0f;
      }

      RecalculateViewMatrix();
    }
  private:
    virtual void RecalculateViewMatrix() override;

    glm::vec3 Position, Front, Up, Right, WorldUp;
    float Yaw, Pitch, MouseSpeed, MouseSensitivity, Zoom;
  };
}
