#pragma once

#include "Core.h"
#include "engine/core/Timestep.h"
#include "events/Event.h"
#include "events/ApplicationEvent.h"
#include "Window.h"

#include "engine/renderer/Shader.h"
#include "engine/renderer/Buffer.h"
#include "engine/renderer/VertexArray.h"


#include "imgui/ImGuiLayer.h"
#include "LayerStack.h"

#include "engine/renderer/OrthographicCamera.h"
#include "engine/core/Timestep.h"

namespace Engine {
  /**
   * Main entry point
   */
  class BE_API Application
  {
    public:

      /**
       * Constructor.
       */
      Application();
      virtual ~Application();

      void Run();

      void OnEvent(Event& e);

      void PushLayer(Layer* layer);
      void PushOverlay(Layer* overlay);

      bool IsRunning() const { return m_Running; }
      inline static Application& Get() { return *s_Instance; };
      inline Window& GetWindow() { return *m_Window; };
    private:
      bool OnWindowClose(WindowCloseEvent&);
      Scope<Window> m_Window;
      ImGUILayer* m_ImGuiLayer;
      bool m_Running = true;
      LayerStack m_LayerStack;
      Timestep m_FrameLastTime{0.f};
      static Application* s_Instance;
  };

  // TODO: by client
  Application* CreateApplication();
}

