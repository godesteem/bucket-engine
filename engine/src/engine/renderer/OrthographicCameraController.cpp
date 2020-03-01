/**
 * File              : OrthographicCameraController.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 29.02.2020
 * Last Modified Date: 01.03.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include "bepch.h"
#include "OrthographicCameraController.h"
#include "engine/Input.h"
#include "engine/KeyCodes.h"
#include "engine/MouseButtonCodes.h"
#include "RenderCommand.h"
#include <imgui/imgui.h>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

namespace Engine {
  OrthographicCameraController::OrthographicCameraController(const std::string& name)
  : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),
  m_CameraPosition(0.0f, 0.0f, 3.0f)
  {}
  OrthographicCameraController::~OrthographicCameraController()
  {}

  void OrthographicCameraController::OnAttach(){}
  void OrthographicCameraController::OnDetach(){}

  void OrthographicCameraController::OnUpdate(Timestep ts){
    {
      if (Input::IsKeyPressed(BE_KEY_LEFT)) {
        m_CameraPosition.x -= m_CameraSpeed * ts;
      } else if (Input::IsKeyPressed(BE_KEY_RIGHT)) {
        m_CameraPosition.x += m_CameraSpeed * ts;
      }
      if (Input::IsKeyPressed(BE_KEY_UP)) {
        m_CameraPosition.y -= m_CameraSpeed * ts;
      } else if (Input::IsKeyPressed(BE_KEY_DOWN)) {
        m_CameraPosition.y += m_CameraSpeed * ts;
      }
    }
    {
      if(Input::IsKeyPressed(BE_KEY_W)) {
        m_CameraPosition.z += m_CameraSpeed * ts;
      } else if(Input::IsKeyPressed(BE_KEY_S)) {
        m_CameraPosition.z -= m_CameraSpeed * ts;
      }
      if (Input::IsKeyPressed(BE_KEY_A)) {
        m_CameraPosition.x -= m_CameraSpeed * ts;
      } else if (Input::IsKeyPressed(BE_KEY_D)) {
        m_CameraPosition.x += m_CameraSpeed * ts;
      }
    }
    {
      float xpos = Engine::Input::GetMouseX();
      float ypos = Engine::Input::GetMouseY();

      if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
      }

      float xoffset = xpos - lastX;
      float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

      lastX = xpos;
      lastY = ypos;
      m_Camera.ProcessMouseMovement(xoffset, yoffset);
    }

    m_Camera.SetPosition(m_CameraPosition);
  }

  void OrthographicCameraController::OnEvent(Event& event){}
  void OrthographicCameraController::OnImGuiRender(){
    ImGui::Begin("Camera");
    ImGui::Text("Camera Position (%d, %d, %d)", (int)m_CameraPosition.x, (int)m_CameraPosition.y, (int)m_CameraPosition.z);
    ImGui::Text("Cursor Position (%d, %d)", (int)Engine::Input::GetMouseX(), (int)Engine::Input::GetMouseY());
    ImGui::PushItemWidth(120);
    ImGui::SliderFloat("x", &m_CameraPosition.x, 0.0f, 10.0f, "%.0f");
    ImGui::SameLine(160);
    ImGui::SliderFloat("y", &m_CameraPosition.y, 0.0f, 10.0f, "%.0f");
    ImGui::SameLine();
    ImGui::SliderFloat("z", &m_CameraPosition.z, 0.0f, 10.0f, "%.0f");
    ImGui::SliderFloat("Yaw", &m_Camera.Yaw, 0.0f, 90.0f, "%.0f");
    ImGui::SliderFloat("Pitch", &m_Camera.Pitch, 0.0f, 90.0f, "%.0f");
    ImGui::PopItemWidth();
    ImGui::End();
  }
}
