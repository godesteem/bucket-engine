/**
 * File              : ImGuiLayer.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 18.02.2020
 * Last Modified Date: 18.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once

#include "engine/Layer.h"

namespace Engine {
  class ImGUILayer: public Layer
  {
    public:

      ImGUILayer();
      ~ImGUILayer();

      void OnAttach();
      void OnDetach();
      void OnUpdate();
      void OnEvent(Event& e);
    private:
      float m_Time = 0.0f;
  };
}
