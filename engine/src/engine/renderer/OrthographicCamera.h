/**
 * File              : OrthographicCamera.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 23.02.2020
 * Last Modified Date: 01.03.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once
#include "engine/Log.h"
#include "engine/core/Timestep.h"
#include <glm/glm.hpp>
#include "engine/KeyCodes.h"
#include "engine/MouseButtonCodes.h"
#include "RenderCommand.h"

namespace Engine {
  const float YAW = -90.0f;
  const float PITCH = 0.0f;
  const float SPEED = 2.5f;
  const float SENSITIFITY = 0.05f;
  const float ZOOM = 45.0f;


  class Camera
  {
  public:
    Camera(glm::mat4 projection, glm::mat4 view);
    void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix();};
    void SetRotation(glm::vec2 rotation) { m_Rotation = rotation; RecalculateViewMatrix();};

    virtual void OnUpdate(Timestep &ts) = 0;
    glm::vec3& GetPosition() {return m_Position; };
    glm::vec2 GetRotation() const { return m_Rotation; };
    
    const glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; };
    const glm::mat4& GetViewMatrix() { return m_ViewMatrix; };
    const glm::mat4& GetViewProjectionMatrix() { return m_ViewProjectionMatrix; };

    virtual void RecalculateViewMatrix() = 0;
  protected:
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ViewProjectionMatrix;

    glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
    glm::vec2 m_Rotation = {0.0f, 0.0f};
    float m_Speed = 10.0f;
  };
  
  class OrthographicCamera: public Camera
  {
  public:
    virtual void OnUpdate(Timestep &ts) override;

  private:
    virtual void RecalculateViewMatrix() override;
  };
  
  class ThirdPersonCamera: public Camera
  {
  public:
    ThirdPersonCamera(float left, float right, float bottom, float top);

    virtual void OnUpdate(Timestep &ts) override;

    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

  private:
    virtual void RecalculateViewMatrix() override;
    
    glm::vec3 m_Target;
    glm::vec3 m_Front;
    glm::vec3 m_Direction;
    glm::vec3 Position, Front, Up, Right, WorldUp;
  public:
    float Yaw, Pitch, MouseSpeed, MouseSensitivity, Zoom;

    float &GetYaw();

    float &GetPitch();
  };
}
