//
// Created by philipp on 3/21/20.
//

#pragma once

#include "bepch.h"

#include "engine/events/Event.h"
#include "engine/renderer/Mesh.h"
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
    bool hasMesh = false;
    bool hasCollisionShape = false;
    std::string meshFileName;

    KineticBodyProps(const std::string& name, glm::vec3 pos, const std::string& meshFile = "")
    : Name(name), Position(pos)
    {
      if(!meshFile.empty()){
        meshFileName = meshFile;
        hasMesh = true;
      }
    }
  };
  class KineticBody {
  public:
    using EventCallbackFn = std::function<void(Event&)>;
    explicit KineticBody(const KineticBodyProps& props = KineticBodyProps("Player", glm::vec3(0.0f), "sandbox/assets/models/Example.obj"));
    ~KineticBody() = default;

    inline void SetEventCallback(const EventCallbackFn& callback) {m_Data.EventCallback = callback; };

    void OnUpdate(Timestep ts) const;

  private:
    void Init(const KineticBodyProps& props);
  private:
    Ref<Mesh> m_Mesh;
    CollisionShape m_Shape;
    float m_Gravity;
    float m_Speed;
    glm::vec3 m_Position;

    struct KinematicBodyData {
      std::string Name;

      EventCallbackFn EventCallback;
    };
    KinematicBodyData m_Data;
  };
}
