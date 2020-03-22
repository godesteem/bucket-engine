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
  }

}
