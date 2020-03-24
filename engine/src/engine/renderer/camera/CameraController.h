#pragma once

#include "engine/core/Layer.h"
#include "ThirdPersonCamera.h"
#include "OrthographicCamera.h"

namespace Engine {
  class CameraController
  {
  public:
    CameraController(const std::string& name = "Camera", CameraType type = CameraType::Default);
    ~CameraController() = default;

    void OnAttach();
    void OnDetach();
    void OnUpdate(Timestep ts);
    void OnEvent(Event& event);
    void OnImGuiRender();

    inline Camera& GetCamera() { return m_Camera; };
  private:
    Camera m_Camera;

    std::string m_Name;
  };
}
