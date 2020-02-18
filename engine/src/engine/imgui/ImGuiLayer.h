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
      bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
      bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
      bool OnMouseMovedEvent(MouseMovedEvent& e);
      bool OnMouseScrolledEvent(MouseScrollEvent& e);
      bool OnKeyPressedEvent(KeyPressedEvent& e);
      bool OnKeyReleasedEvent(KeyReleasedEvent& e);
      //bool OnKeyTypedEvent(KeyTypedEvent& e);
      bool OnWindowResizeEvent(WindowResizeEvent& e);

      float m_Time = 0.0f;
  };
}
