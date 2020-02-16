/**
 * File              : Application.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 15.02.2020
 * Last Modified Date: 16.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */

#include "Application.h"
#include "bepch.h"


#include "engine/events/ApplicationEvent.h"
#include "engine/Log.h"

namespace Engine {
  
  Application::Application(){

  }

  Application::~Application(){

  }

  void Application::Run(){
    WindowResizeEvent e(1280, 720);
    BE_TRACE(e);
    
    while(1){

    }
  }


}
