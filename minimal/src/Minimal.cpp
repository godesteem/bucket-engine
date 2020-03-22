//
// Created by philipp on 3/22/20.
//

#include <engine.h>


class Minimal: public Engine::Application
{
public:
  Minimal() {};
  ~Minimal() = default;
};

Engine::Application* Engine::CreateApplication(){
  return new Minimal();
}
