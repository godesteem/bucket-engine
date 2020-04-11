#include "SandboxApp.h"

Engine::Application* Engine::CreateApplication(){
  return new Sandbox();
}

Sandbox::Sandbox()
{
  PushLayer(new ExampleLayer());
  //PushLayer(new Engine::Level("Level 0-0"));
  PushLayer(new GameWorld());
}
