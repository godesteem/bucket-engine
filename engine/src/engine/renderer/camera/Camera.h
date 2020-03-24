//
// Created by phil on 24.03.20.
//
#pragma once
#include "engine/core/io/Log.h"
#include "engine/core/Timestep.h"
#include <iterator>
#include "engine/core/io/KeyCodes.h"
#include "engine/core/io/MouseButtonCodes.h"
#include "engine/renderer/RenderCommand.h"

namespace Engine {
  enum class CameraType{
    None = 0, Orthographic = 1, ThirdPerson = 2, Default = 2
  };
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

}
