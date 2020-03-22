//
// Created by philipp on 3/21/20.
//

#pragma once

#include <glm/glm.hpp>

namespace Engine {
  class CollisionShape {

  };
  class RectangularCollisionShape: public CollisionShape
  {

  };
  class SphereCollisionShape: public CollisionShape
  {

  };
  class KineticBody {
  public:
    KineticBody();
    ~KineticBody() = default;

  private:
    CollisionShape m_Shape;
    float m_Gravity = 9.81;
    float m_Speed = 10.0f;
    glm::vec3 m_Position;
  };
}
