//
// Created by phil on 14.03.20.
//
#pragma once

#include <engine.h>

struct vec3 {
  float x, y, z;
};

struct vec2 {
  float x, y;
};

class GameWorld: public Engine::Layer
{
public:
  GameWorld();
  GameWorld(Engine::Ref<Engine::VertexBuffer> vb, Engine::Ref<Engine::IndexBuffer> ib, const std::string& name);

  virtual void OnUpdate(Engine::Timestep ts) override {
    m_Mesh->OnUpdate(ts);
  };
  virtual void OnImGuiRender() override {
    ImGui::Begin("World Mesh");
    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_FittingPolicyDefault_ | ImGuiTabBarFlags_Reorderable;
    if (ImGui::BeginTabBar("##tabs", tab_bar_flags)) {
      m_Mesh->OnImGuiRender();
      ImGui::EndTabBar();
    }
    ImGui::End();
  }

  Engine::Ref<Engine::Mesh> m_Mesh;
};

GameWorld::GameWorld(Engine::Ref<Engine::VertexBuffer> vb, Engine::Ref<Engine::IndexBuffer> ib, const std::string &name)
: Layer(name)
{
  m_Mesh = Engine::Mesh::Create(vb, ib, "/home/phil/work/private/games/bucket-engine/sandbox/assets/shaders/World.glsl");
}
void noise(vec3& vec){
  vec.x = vec.x;
  vec.y = sqrtf(vec.x);
  vec.z = vec.z;
}
GameWorld::GameWorld()
: Layer("World"){
  std::string shaderFile = "/home/phil/work/private/games/bucket-engine/sandbox/assets/shaders/World.glsl";
  const int vertexCount = 510;
  const int coordinateCount = 5;

  float vertices[vertexCount * coordinateCount];
  float _x[] = {-0.5f, 0.5f, 0.5f, 0.5f, -0.5f, -0.5f};
  float _z[] = {-0.5f, -0.5f, 0.5f, 0.5f, 0.5f, -0.5f};
  float textCoordX[] = {0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f};
  float textCoordY[] = {0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f};
  float padding = 1.0f;
  float factor = 1.0f;
  for(int index = 0; index < vertexCount * coordinateCount; index+=5){
    int realIndex = index/5;
    vec2 textCoord = {textCoordX[realIndex%6], textCoordY[realIndex%6]};
    vec3 pos = {_x[realIndex%6] + padding, 0.0f, _z[realIndex%6]};
    noise(pos);
    vertices[index] = pos.x;
    vertices[index + 1] = pos.y;
    vertices[index + 2] = pos.z;
    vertices[index + 3] = textCoord.x;
    vertices[index + 4] = textCoord.y;
    if(realIndex%6==0&&realIndex!=0) padding+=factor;
  };
  uint32_t indices[vertexCount];
  for(int i=1; i<=vertexCount; ++i){
    indices[i] = i;
  }

  Engine::Ref<Engine::IndexBuffer> ia;
  ia.reset(Engine::IndexBuffer::Create(indices, vertexCount));

  Engine::Ref<Engine::VertexBuffer> vb;
  vb.reset(Engine::VertexBuffer::Create(vertices, vertexCount * coordinateCount));
  vb->SetLayout({
      { Engine::ShaderDataType::Float3, "position" },
      { Engine::ShaderDataType::Float2, "textCord" }
  });
  m_Mesh = Engine::Mesh::Create(vb, ia, shaderFile);
  m_Mesh->SetName("World");
}
