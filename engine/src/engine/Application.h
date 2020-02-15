/**
 * File              : Application.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 15.02.2020
 * Last Modified Date: 15.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once

#include "Core.h"
#include <iostream>

namespace Engine {

  void Print(){
    std::cout << "Hello World!\n";
  }
  
  class Application
  {
    public:
      Application();
      virtual ~Application();
      
      void Run();
  };
  
  // TODO: by client
  Application* CreateApplication();
}

