#pragma once

#include "engine/Application.h"

//#ifdef BE_PLATFORM_WINDOWS

//#else

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char **argv){
  Engine::Log::Init();

  auto app = Engine::CreateApplication();
  app->Run();
  delete app;
}

//#endif
