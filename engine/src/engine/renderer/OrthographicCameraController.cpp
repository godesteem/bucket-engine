#include "bepch.h"
#include "OrthographicCameraController.h"
#include "engine/Input.h"
#include <imgui/imgui.h>

namespace Engine {
  OrthographicCameraController::OrthographicCameraController(const std::string& name)
  : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),
    m_Name(name)
  {}

  void OrthographicCameraController::OnAttach(){}
  void OrthographicCameraController::OnDetach(){}

  void OrthographicCameraController::OnUpdate(Timestep ts){
    m_Camera.OnUpdate(ts);
  }

  void OrthographicCameraController::OnEvent(Event& event){}
  void OrthographicCameraController::OnImGuiRender(){
    ImGui::Begin("Camera");
    ImGui::Text("Camera Position (%d, %d, %d)", (int) m_Camera.GetPosition().x, (int) m_Camera.GetPosition().y,
                (int) m_Camera.GetPosition().z);
    ImGui::Text("Cursor Position (%d, %d)", (int)Engine::Input::GetMouseX(), (int)Engine::Input::GetMouseY());
    ImGui::PushItemWidth(120);
    ImGui::SliderFloat("x", &m_Camera.GetPosition().x, 0.0f, 10.0f, "%.0f");
    ImGui::SameLine(160);
    ImGui::SliderFloat("y", &m_Camera.GetPosition().y, 0.0f, 10.0f, "%.0f");
    ImGui::SameLine();
    ImGui::SliderFloat("z", &m_Camera.GetPosition().z, 0.0f, 10.0f, "%.0f");
    ImGui::SliderFloat("Yaw", &m_Camera.GetYaw(), -90.0f, 90.0f, "%.0f");
    ImGui::SliderFloat("Pitch", &m_Camera.GetPitch(), -90.0f, 90.0f, "%.0f");
    ImGui::SliderFloat("Speed", &m_Camera.GetSpeed(), 10.0f, 20.0f, "%f");
    ImGui::PopItemWidth();
    ImGui::End();
  }
}
