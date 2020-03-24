/**
 * File              : OrthographicCameraController.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 29.02.2020
 * Last Modified Date: 01.03.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once

#include "engine/core/Layer.h"
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
