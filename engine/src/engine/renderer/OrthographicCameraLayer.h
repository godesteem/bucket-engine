/**
 * File              : OrthographicCameraLayer.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 29.02.2020
 * Last Modified Date: 29.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once

#include "engine/Layer.h"
#include "OrthographicCamera.h"

namespace Engine {
  class OrthographicCameraLayer
  {
  public:
    OrthographicCameraLayer(const std::string& name = "Camera");
    ~OrthographicCameraLayer();

    void OnAttach();
    void OnDetach();
    void OnUpdate(Timestep ts);
    void OnEvent(Event& event);
    void OnImGuiRender();

    inline Camera& GetCamera() { return m_Camera; };
  private:
    ThirdPersonCamera m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraSpeed = 5.0f;
    
    std::string m_Name;
  };
}
