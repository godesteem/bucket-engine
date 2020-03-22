//
// Created by philipp on 3/21/20.
//

#pragma once

#include "bepch.h"

#include "engine/events/Event.h"
#include "engine/Core.h"
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
  struct KineticBodyProps {
    std::string Name;
    glm::vec3 Position;
    float Gravity = 9.81f;
    float Speed = 10.0f;
  };
  class KineticBody {
  public:
    using EventCallbackFn = std::function<void(Event&)>;
    KineticBody(const KineticBodyProps& props);
    ~KineticBody() = default;

    void Init(const KineticBodyProps& props);

  private:
    CollisionShape m_Shape;
    float m_Gravity = 9.81;
    float m_Speed = 10.0f;
    glm::vec3 m_Position;

    struct KinematicBodyData {
      std::string Name;

      EventCallbackFn EventCallback;
    };
    KinematicBodyData m_Data;
  };
}
