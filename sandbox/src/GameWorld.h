//
// Created by phil on 14.03.20.
//
#pragma once

#include <engine.h>

struct vec3 {
  float x, y, z;
  vec3& operator=(const vec3& other){
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    return *this;
  }
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
  static void GenerateVertices(const std::string &fileName);

  Engine::Ref<Engine::Mesh> m_Mesh;
};

GameWorld::GameWorld(Engine::Ref<Engine::VertexBuffer> vb, Engine::Ref<Engine::IndexBuffer> ib, const std::string &name)
: Layer(name)
{
  m_Mesh = Engine::Mesh::Create(vb, ib, "sandbox/assets/shaders/World.glsl");
}
void GameWorld::GenerateVertices(const std::string &fileName) {
  const int rowCount = 80;
  const int columnCount = rowCount;
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
    float paddingX = -(rowCount / 2.0f) * factor;
    for(int column=0; column<columnCount; column++){
      for(int index = 0; index<verticesForSquare; index++){
        vec3 pos = {_x[index] + paddingX, 0.0f, _z[index] + paddingY};

        vec2 texture = {textCoordX[index], textCoordY[index]};
        vertices[currentIndex] = pos.x;
        vertices[currentIndex + 1] = 10.0f * sinf(10 * (pos.x*pos.x+pos.z*pos.z))/10;
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
  for(int i=0; i<vertexCount; ++i){
    indices[i] = i;
  }

  Engine::ObjFile::CreateObjFile(vertices, vertexCount, Engine::ObjFile::VertexCategory::VertexCategoryVertex | Engine::ObjFile::VertexCategory::VertexCategoryNormal, indexCount, indices, vertexCount, fileName);

}
GameWorld::GameWorld()
: Layer("World"){
  std::string shaderFile = "sandbox/assets/shaders/World.glsl";
  std::string objFile = "sandbox/assets/models/World.obj";
  GenerateVertices(objFile);
  m_Mesh = Engine::Mesh::Create(objFile, shaderFile);
  m_Mesh->SetName("World");
};
