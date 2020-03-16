/**
 * File              : Level.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 09.03.2020
 * Last Modified Date: 09.03.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include "bepch.h"
#include "Level.h"

namespace Engine {
  Level::Level(const std::string& name, float height, float width)
    :Layer(name)
  {
    m_World = Mesh::Create("sandbox/assets/models/Example.obj", "sandbox/assets/shaders/Example.glsl");
  }

  void Level::OnAttach() {};
  void Level::OnDetach() {};
  void Level::OnUpdate(Timestep ts) {
    m_World->OnUpdate(ts);
    for(const auto& obj : m_Objects){
      obj->OnUpdate(ts);
    }
  };
  void Level::OnEvent(Event& event) {};
  void Level::OnImGuiRender() {};
}
