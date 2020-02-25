/**
 * File              : Application.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 15.02.2020
 * Last Modified Date: 25.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once

#include "Core.h"
#include "events/Event.h"
#include "events/ApplicationEvent.h"
#include "Window.h"

#include "engine/renderer/Shader.h"
#include "engine/renderer/Buffer.h"
#include "engine/renderer/VertexArray.h"


#include "imgui/ImGuiLayer.h"
#include "LayerStack.h"

#include "engine/renderer/OrthographicCamera.h"

namespace Engine {

  class BE_API Application
  {
    public:
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
      std::unique_ptr<Window> m_Window;
      ImGUILayer* m_ImGuiLayer;
      bool m_Running = true;
      LayerStack m_LayerStack;

      static Application* s_Instance;
  };
  
  // TODO: by client
  Application* CreateApplication();
}

