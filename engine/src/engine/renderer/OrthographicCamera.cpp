/**
 * File              : OrthographicCamera.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 23.02.2020
 * Last Modified Date: 25.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include "bepch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Engine {

  OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    :m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
  {
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
  };
  void OrthographicCamera::RecalculateViewMatrix(){
    glm::mat4 tranform = glm::translate(glm::mat4(1.0f), m_Position) *
      glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

    m_ViewMatrix = glm::inverse(tranform);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
  }
    

}
