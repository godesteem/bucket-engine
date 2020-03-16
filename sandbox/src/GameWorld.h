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
  m_Mesh = Engine::Mesh::Create(vb, ib, "sandbox/assets/shaders/World.glsl");
}
void noise(vec3& vec){
  vec.x = vec.x;
  vec.y = vec.y;
  vec.z = vec.z;
}
GameWorld::GameWorld()
: Layer("World"){
  std::string shaderFile = "sandbox/assets/shaders/World.glsl";
  const int rowCount = 10;
  const int columnCount = 5;
  const int verticesForSquare = 6;
  const int vertexCount = verticesForSquare * rowCount * columnCount;
  const int indexCount = 5;
  float factor = 1.0f;

  float vertices[vertexCount * indexCount];
  float _x[verticesForSquare] = {0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f};
  float _z[verticesForSquare] = {0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f};
  float textCoordX[] = {0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f};
  float textCoordY[] = {0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f};

  float paddingY = 0.0f;
  size_t currentIndex = 0;
  for(int row=0; row<rowCount; row++){
    float paddingX = 0.0f;
    for(int column=0; column<columnCount; column++){
      for(int index = 0; index<verticesForSquare; index++){
        vec3 pos = {_x[index] + paddingX, 0.0f, _z[index] + paddingY};
        vec2 texture = {textCoordX[index], textCoordY[index]};
        vertices[currentIndex] = pos.x;
        vertices[currentIndex + 1] = pos.y;
        vertices[currentIndex + 2] = pos.z;
        vertices[currentIndex + 3] = texture.x;
        vertices[currentIndex + 4] = texture.y;
        currentIndex+=indexCount;
      }
      paddingX += factor;
    }
    paddingY += factor;
  }

  uint32_t indices[vertexCount];
  for(int i=1; i<=vertexCount; ++i){
    indices[i] = i;
  }

  Engine::ObjFile::CreateObjFile(vertices, vertexCount, Engine::ObjFile::VertexCategory::VertexCategoryVertex | Engine::ObjFile::VertexCategory::VertexCategoryNormal, indexCount, indices, vertexCount, "sandbox/assets/models/World.obj");
  m_Mesh = Engine::Mesh::Create("sandbox/assets/models/World.obj", shaderFile);
  m_Mesh->SetName("World");
};
