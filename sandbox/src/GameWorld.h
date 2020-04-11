//
// Created by phil on 14.03.20.
//
#pragma once

#include <engine.h>

class GameWorld : public Engine::Layer
{
public:
  GameWorld();
  GameWorld(Engine::Ref<Engine::VertexBuffer> vb, Engine::Ref<Engine::IndexBuffer> ib, const std::string& name);

  virtual void OnUpdate(Engine::Timestep ts) override;
  virtual void OnImGuiRender() override;
  static void GenerateVertices(const std::string& fileName);

  Engine::Ref<Engine::Mesh> mesh_ground;
};
