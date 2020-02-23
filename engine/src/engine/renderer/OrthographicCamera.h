/**
 * File              : OrthographicCamera.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 23.02.2020
 * Last Modified Date: 23.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once

#include <glm/glm.hpp>

namespace Engine {
  
  class OrthographicCamera
  {
  public:
    OrthographicCamera(float left, float right, float bottom, float top);
    
    void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix();};
    void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix();};

    glm::vec3& GetPosition() {return m_Position; };
    float GetRotation() const { return m_Rotation; };
    
    const glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; };
    const glm::mat4& GetViewMatrix() { return m_ViewMatrix; };
    const glm::mat4& GetViewProjectionMatrix() { return m_ViewProjectionMatrix; };
  private:
    void RecalculateViewMatrix();

  private:
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ViewProjectionMatrix;

    glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
    float m_Rotation = 0.0f;
  };
}
