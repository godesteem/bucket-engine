/**
 * File              : OrthographicCamera.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 23.02.2020
 * Last Modified Date: 09.03.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once
#include "engine/Log.h"
#include "engine/core/Timestep.h"
#include <glm/glm.hpp>
#include <iterator>
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
    struct CameraStack
    {
    public:
      CameraStack(){};
      inline void AddCamera(Camera *c) {
        for(auto cam: m_Stack){
          if(cam->IsActive())
            cam->m_IsActive = false;
        }
        m_Stack.push_back(c);
      }
      inline Camera* GetActiveCamera() {
        for(auto cam : m_Stack){
          if(cam->IsActive())
            return cam;
        }
        BE_CORE_ASSERT(false, "No camera active!");
      }
      std::vector<Camera*> m_Stack;
    };
  public:
    Camera(glm::mat4 projection, glm::mat4 view);
    void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix();};
    void SetRotation(glm::vec2 rotation) { m_Rotation = rotation; RecalculateViewMatrix();};

    virtual void OnUpdate(Timestep &ts) = 0;
    glm::vec3& GetPosition() {return m_Position; };
    glm::vec2 GetRotation() const { return m_Rotation; };
    float& GetSpeed() { return m_Speed; }
    
    const glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; };
    const glm::mat4& GetViewMatrix() { return m_ViewMatrix; };
    const glm::mat4& GetViewProjectionMatrix() { return m_ViewProjectionMatrix; };

    virtual void RecalculateViewMatrix() = 0;

    bool IsActive() { return m_IsActive; };

    static CameraStack* camStack;
    static Camera* GetActiveCamera() { return camStack->GetActiveCamera(); }
  protected:
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ViewProjectionMatrix;

    glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
    glm::vec2 m_Rotation = {0.0f, 0.0f};
    float m_Speed = 10.0f;
    bool m_IsActive = true;
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
