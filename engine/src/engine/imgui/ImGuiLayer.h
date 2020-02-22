/**
 * File              : ImGuiLayer.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 18.02.2020
 * Last Modified Date: 18.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once

#include "engine/Layer.h"
#include "engine/events/MouseEvent.h"
#include "engine/events/ApplicationEvent.h"
#include "engine/events/KeyEvent.h"

// TEMPORARY
#include <GLFW/glfw3.h>

namespace Engine {
  class ImGUILayer: public Layer
  {
    public:

      ImGUILayer();
      ~ImGUILayer();

      virtual void OnAttach() override ;
      virtual void OnDetach() override ;
      virtual void OnImGuiRender() override ;

      void Begin();
      void End();
  private:
      float m_Time = 0.0f;
  };
}
