/**
 * File              : Application.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 15.02.2020
 * Last Modified Date: 16.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include "bepch.h"
#include "Application.h"
#include "GLFW/glfw3.h"


#include "engine/events/ApplicationEvent.h"
#include "engine/Log.h"

namespace Engine {
  
  Application::Application(){
    m_Window = std::unique_ptr<Window>(Window::Create());
  }

  Application::~Application(){

  }

  void Application::Run(){
    while(m_Running){
      glClearColor(1, 0, 1, 1);
      glClear(GL_COLOR_BUFFER_BIT);
      m_Window->OnUpdate();
    }
  }


}
