//
// Created by philipp on 3/21/20.
//

#pragma once

#include "bepch.h"

#include "engine/events/Event.h"
#include "engine/renderer/mesh/Mesh.h"
#include "engine/renderer/camera/OrthographicCameraController.h"
#include "engine/core/Core.h"
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
    // Utils
    std::string Name;

    // Mesh
    std::string meshFileName;
    bool hasMesh = false;

    // Collision
    bool hasCollisionShape = false;

    // Movement
    glm::vec3 Position;
    float Gravity = 9.81f;
    float Speed = 10.0f;
    bool hasCamera = false;

    KineticBodyProps(const std::string& name, glm::vec3 pos, const std::string& meshFile = "", bool hasCam = true)
    : Name(name), Position(pos), hasCamera(hasCam)
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

    void OnUpdate(Timestep ts);
    void OnEvent(Event& event);
    void UpdatePosition(Timestep ts);

  private:
    void Init(const KineticBodyProps& props);
  private:
    Ref<Mesh> m_Mesh;
    CollisionShape m_Shape;
    float m_Gravity;
    float m_Speed;
    glm::vec3 m_Position;
    bool hasCamera = false;
    Ref<OrthographicCameraController> m_CameraLayer;

    struct KinematicBodyData {
      std::string Name;

      EventCallbackFn EventCallback;
    };
    KinematicBodyData m_Data;

  };
}
