/**
 * File              : Application.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 15.02.2020
 * Last Modified Date: 17.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once

#include "Core.h"
#include "events/Event.h"
#include "events/ApplicationEvent.h"
#include "Window.h"

namespace Engine {

  class BE_API Application
  {
    public:
      Application();
      virtual ~Application();
      
      void Run();

      void OnEvent(Event& e);
    private:
      bool OnWindowClose(WindowCloseEvent&);
      std::unique_ptr<Window> m_Window;
      bool m_Running = true;
  };
  
  // TODO: by client
  Application* CreateApplication();
}

