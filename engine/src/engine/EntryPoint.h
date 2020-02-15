/**
 * File              : EntryPoint.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 15.02.2020
 * Last Modified Date: 15.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once

#ifdef BE_PLATFORM_WINDOWS

#else
extern Engine::Application* Engine::CreateApplication();

int main(int argc, char **argv){
  std::cout << "Engine starting..\n";
  auto app = Engine::CreateApplication();
  app->Run();
  delete app;
}

#endif
