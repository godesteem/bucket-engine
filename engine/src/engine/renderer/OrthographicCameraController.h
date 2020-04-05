#pragma once

#include "engine/Layer.h"
#include "OrthographicCamera.h"

namespace Engine {
  class OrthographicCameraController
  {
  public:
    OrthographicCameraController(const std::string& name = "Camera");
    ~OrthographicCameraController() = default;

    void OnAttach();
    void OnDetach();
    void OnUpdate(Timestep ts);
    void OnEvent(Event& event);
    void OnImGuiRender();

    inline Camera& GetCamera() { return m_Camera; };
  private:
    ThirdPersonCamera m_Camera;

    std::string m_Name;
  };
}
