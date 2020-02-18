/**
 * File              : SandboxApp.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 15.02.2020
 * Last Modified Date: 18.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */

#include <engine.h>


class ExampleLayer: public Engine::Layer
{
  public:
    ExampleLayer()
      :Layer("Example")
    {}
    
    void OnUpdate() override {
      BE_INFO("ExampleLayer::OnUpdate");
    }
    void OnEvent(Engine::Event& event) override {
      BE_INFO("{0}", event);
    }
};

class Sandbox: public Engine::Application
{
  public:
    Sandbox()
    {
      PushLayer(new ExampleLayer());
      PushOverlay(new Engine::ImGUILayer());
    }

    ~Sandbox()
    {

    }
};

Engine::Application* Engine::CreateApplication(){
  return new Sandbox();
}
