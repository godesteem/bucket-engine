#pragma once
#define ENGINE_ENTRY_POINT
#include <engine.h>

#include "GameWorld.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>

// camera
//m_Texture = Engine::Texture2D::Create("sandbox/assets/portal.png");
//const std::string textureSrc = "";
const std::string textureSrc  = "sandbox/assets/Checkerboard.png";
const std::string textureSrc2 = "sandbox/assets/portal.png";

class ExampleLayer : public Engine::Layer
{
  enum Objects
  {
    Suzanne,
    Triangle,
    Cube3D,
    Cube3D6,
    Cube2D,
    Grid,
    ImageTexture,
    Cube3DMan
  };

public:
  ExampleLayer();

  void OnUpdate(Engine::Timestep ts) override;
  void OnEvent(Engine::Event& event) override;
  bool OnKeyPressedEvent(Engine::KeyPressedEvent& event) { return false; }

  virtual void OnImGuiRender() override;

private:
  Engine::ShaderLibrary m_ShaderLibrary;
  Engine::Ref<Engine::Shader> m_Shader;
  Engine::Ref<Engine::Shader> m_FlatColorShader;

  Engine::Ref<Engine::VertexArray> m_VertexArray;
  Engine::Ref<Engine::VertexArray> m_SquareVA;

  Engine::Ref<Engine::Texture2D> m_Texture;
  Engine::Ref<Engine::Texture2D> m_PortalTexture;

  Engine::OrthographicCameraController m_PlayerCameraLayer;

  Engine::Ref<Engine::Mesh> m_Suzanne;
  Engine::Ref<Engine::Mesh> m_Cube;
  Engine::Ref<Engine::Mesh> m_Cube6;
  std::vector<Engine::Ref<Engine::Mesh>> m_Models;

  float m_SquareMoveSpeed = 5.0f;
  bool objects[8]         = { false, false, false, false, false, false, false, false };

  glm::vec3 m_SquarePosition;
  glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Engine::Application
{
public:
  Sandbox();
  ~Sandbox() = default;
};
