#pragma once

#include "engine/Layer.h"
#include "engine/renderer/Mesh.h"

namespace Engine {
  class Level: public Layer
  {
    public:
      Level(const std::string& name, float height=1290.0f, float width=720.0f);
      virtual void OnAttach() override;
      virtual void OnDetach() override;
      virtual void OnUpdate(Timestep ts) override;
      virtual void OnEvent(Event& event) override;
      virtual void OnImGuiRender() override;
    private:
      std::vector<Ref<Mesh>> m_Objects;
      Ref<Mesh> m_World;
  };
}
