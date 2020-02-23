/**
 * File              : SandboxApp.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 15.02.2020
 * Last Modified Date: 18.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */

#include <engine.h>
#include <imgui/imgui.h>


class ExampleLayer: public Engine::Layer
{
  public:
    ExampleLayer()
      :Layer("Example")
    {}

    virtual void OnImGuiRender() override {
      ImGui::Begin("Test");
      ImGui::Text("Hello World!");
      ImGui::End();
    }
    
    void OnUpdate() override {
      //BE_INFO("ExampleLayer::OnUpdate");

      if(Engine::Input::IsKeyPressed(BE_KEY_TAB)){
        BE_INFO("Tab key is pressed.");
      }
    }
    void OnEvent(Engine::Event& event) override {
      //BE_INFO("{0}", event);
      if(event.GetEventType() == Engine::EventType::KeyPressed){
        auto& e = (Engine::KeyPressedEvent&)event;
        BE_TRACE("{0}", (char) e.GetKeyCode());
      }
    }
};

class Sandbox: public Engine::Application
{
  public:
    Sandbox()
    {
      PushLayer(new ExampleLayer());
    }

    ~Sandbox()
    {

    }
};

Engine::Application* Engine::CreateApplication(){
  return new Sandbox();
}
