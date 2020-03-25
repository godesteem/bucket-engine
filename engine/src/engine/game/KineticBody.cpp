//
// Created by philipp on 3/21/20.
//

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
      glm::vec3 position(m_Position + 20.0f * m_CameraLayer->GetCamera().GetDirection());
      m_Mesh->SetPosition(position);
      m_Mesh->SetScale(0.001f);
    }
  }

  void KineticBody::OnUpdate(Timestep ts) {
    // TODO: let camera follow mesh, mesh will be controlled from here.
    // TODO: Add scrolling for ZOOM
    if(this->hasCamera){
      m_CameraLayer->OnUpdate(ts);
      m_Position = m_CameraLayer->GetCamera().GetPosition();
    } else {
      UpdatePosition(ts);
    }
    if(this->m_Mesh){
      glm::vec3 position(m_Position + 20.0f * m_CameraLayer->GetCamera().GetDirection());
      m_Mesh->SetPosition(position);
      m_Mesh->OnUpdate(ts);
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
