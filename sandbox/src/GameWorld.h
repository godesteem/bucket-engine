//
// Created by phil on 14.03.20.
//
#pragma once

#include <engine.h>

class GameWorld: public Engine::Layer
{
public:
  GameWorld();
  GameWorld(Engine::Ref<Engine::VertexBuffer> vb, Engine::Ref<Engine::IndexBuffer> ib, const std::string& name);;

  virtual void OnUpdate(Engine::Timestep ts) override {
    m_Mesh->OnUpdate(ts);
  };

  Engine::Ref<Engine::Mesh> m_Mesh;
};

GameWorld::GameWorld(Engine::Ref<Engine::VertexBuffer> vb, Engine::Ref<Engine::IndexBuffer> ib, const std::string &name)
: Layer(name)
{
  m_Mesh = Engine::Mesh::Create(vb, ib, "");
}

GameWorld::GameWorld()
: Layer("World"){
  std::string objFile = "/home/phil/work/private/games/bucket-engine/sandbox/assets/models/Plane.obj";
  std::string shaderFile = "/home/phil/work/private/games/bucket-engine/sandbox/assets/shaders/Plane.glsl";
  m_Mesh = Engine::Mesh::Create(objFile, shaderFile);
}
