//
// Created by phil on 14.03.20.
//
#pragma once

#include <engine.h>

class GameWorld
  : public Engine::Layer
{
public:
  GameWorld()
    : Layer("World")
  {
    std::string shaderFile = "sandbox/assets/shaders/World.glsl";
    std::string objFile    = "sandbox/assets/models/World.obj";
    GenerateVertices(objFile);
    m_Mesh = Engine::Mesh::Create(objFile, shaderFile);
    m_Mesh->SetName("World");
  }
  GameWorld(Engine::Ref<Engine::VertexBuffer> vb, Engine::Ref<Engine::IndexBuffer> ib, const std::string& name);

  virtual void OnUpdate(Engine::Timestep ts) override { m_Mesh->OnUpdate(ts); };
  virtual void OnImGuiRender() override
  {
    ImGui::Begin("World Mesh");
    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_FittingPolicyDefault_ | ImGuiTabBarFlags_Reorderable;
    if (ImGui::BeginTabBar("##tabs", tab_bar_flags))
    {
      m_Mesh->OnImGuiRender();
      ImGui::EndTabBar();
    }
    ImGui::End();
  }
  static void GenerateVertices(const std::string& fileName);

  Engine::Ref<Engine::Mesh> m_Mesh;
};
