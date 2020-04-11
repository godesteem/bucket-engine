//
// Created by philipp on 3/21/20.
//

#include <engine/core/io/Input.h>
#include "KineticBody.h"

namespace Engine {

  KineticBody::KineticBody(const KineticBodyProps& props) {
    Init(props);
  }

  void KineticBody::Init(const KineticBodyProps& props) {
    m_Data.Name = props.Name;
    m_Speed = props.Speed;
    m_Gravity = props.Gravity;
    m_Position = props.Position;
    hasCamera = props.hasCamera;

    if(hasCamera){
      m_CameraLayer.reset(new CameraController());
    }
    if(props.hasMesh){
      m_Mesh = Mesh::Create(props.meshFileName, "sandbox/assets/shaders/Player.glsl");
      glm::vec3 position(m_Position + 20.0f * m_CameraLayer->GetCamera().GetTarget());
      m_Mesh->SetPosition(position);
      m_Mesh->SetScale(0.001f);
    }
  }

  void KineticBody::OnUpdate(Timestep tsr) {
    // TODO: let camera follow mesh, mesh will be controlled from here.
    // TODO: Add scrolling for ZOOM
    float ts = std::chrono::duration_cast<std::chrono::milliseconds>(tsr).count() / 1000.0f;
    Camera& camera = m_CameraLayer->GetCamera();
    {
      if (Input::IsKeyPressed(BE_KEY_W)) {
        m_Position += m_Speed * ts * camera.GetFront();
      } else if (Input::IsKeyPressed(BE_KEY_S)) {
        m_Position -= m_Speed * ts * camera.GetFront();
      }
      if (Input::IsKeyPressed(BE_KEY_A)) {
        m_Position += glm::normalize(glm::cross(camera.GetFront(), camera.GetUp())) * (m_Speed * ts);
      } else if (Input::IsKeyPressed(BE_KEY_D)) {
        m_Position -= glm::normalize(glm::cross(camera.GetFront(), camera.GetUp())) * (m_Speed * ts);
      }
    }
    if(this->m_Mesh){
      m_Mesh->SetPosition(m_Position);
      m_Mesh->OnUpdate(tsr);
    }
    if(this->hasCamera){
      m_CameraLayer->GetCamera().SetTarget(m_Position);
      m_CameraLayer->OnUpdate(tsr);
    } else {
      UpdatePosition(tsr);
    }
  }

  void KineticBody::UpdatePosition(Timestep ts) {

  }

  void KineticBody::OnEvent(Event &event) {
//    EventDispatcher dispatcher(event);
    if(hasCamera) {
      m_CameraLayer->OnEvent(event);
    }
  }

}
