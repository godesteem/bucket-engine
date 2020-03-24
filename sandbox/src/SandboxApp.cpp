#include <engine.h>
#include <imgui/imgui.h>
#include "GameWorld.h"

class ExampleLayer: public Engine::Layer
{

  public:
    ExampleLayer()
      :Layer("Example"),
      m_Player()
    {
    }

    void OnUpdate(Engine::Timestep ts) override {
      Engine::Renderer::BeginScene(m_PlayerCameraLayer.GetCamera());

      Engine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1});
      Engine::RenderCommand::Clear();

      m_Player->OnUpdate(ts);
      Engine::Renderer::EndScene();
    }
    void OnEvent(Engine::Event& event) override {

    }
    bool OnKeyPressedEvent(Engine::KeyPressedEvent& event){
      return false;
    }

    virtual void OnImGuiRender() override {
      {
        // Admin panel
        ImGui::Begin("Admin");

        ImGui::End();
      }
      m_PlayerCameraLayer.OnImGuiRender();
    }
  private:
    Engine::OrthographicCameraController m_PlayerCameraLayer;
    Engine::Ref<Engine::KineticBody> m_Player;
};

class Sandbox: public Engine::Application
{
  public:
    Sandbox()
    {
      PushLayer(new ExampleLayer());
      PushLayer(new GameWorld());
    }

    ~Sandbox() = default;
};

Engine::Application* Engine::CreateApplication(){
  return new Sandbox();
}
