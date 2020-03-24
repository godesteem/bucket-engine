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

    if(props.hasMesh){
      m_Mesh = Mesh::Create(props.meshFileName, "sandbox/assets/shaders/Example.glsl");
    }
    if(hasCamera){
      m_CameraLayer.reset(new CameraController());
    }
  }

  void KineticBody::OnUpdate(Timestep ts) {
    BE_CORE_TRACE("KineticBody::OnUpdate");
    if(this->hasCamera){
      m_CameraLayer->OnUpdate(ts);
      m_Position = m_CameraLayer->GetCamera().GetPosition();
    } else {
      UpdatePosition(ts);
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
