//
// Created by phil on 14.03.20.
//
#pragma once

#include <engine.h>
#include <glm/gtc/noise.hpp>

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
    for(const auto& obj : m_Models){
      obj->OnUpdate(ts);
    }
  };
  virtual void OnImGuiRender() override {
    ImGui::Begin("World Mesh");
    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_FittingPolicyDefault_ | ImGuiTabBarFlags_Reorderable;
    if (ImGui::BeginTabBar("##tabs", tab_bar_flags)) {
      for (const auto &obj : m_Models) {
        obj->OnImGuiRender();
      }
      ImGui::EndTabBar();
    }
    ImGui::End();
  }
  void GenerateVertices(const std::string &fileName);

  std::vector<Engine::Ref<Engine::Mesh>> m_Models;
  const int m_MeshCount = 45;
};

GameWorld::GameWorld(Engine::Ref<Engine::VertexBuffer> vb, Engine::Ref<Engine::IndexBuffer> ib, const std::string &name)
: Layer(name)
{
  m_Models.push_back(Engine::Mesh::Create(vb, ib, "sandbox/assets/shaders/World.glsl"));
}
void GameWorld::GenerateVertices(const std::string &fileName) {
// Warning	C6262	Function uses '921780' bytes of stack:  exceeds /analyze:stacksize '16384'.  Consider moving some data to heap.

  const int rowCount = 20;
  const int columnCount = rowCount;
  const int verticesForSquare = 6;
  const int vertexCount = verticesForSquare * rowCount * columnCount;
  const int indexCount = 5;
  float factor = 1.0f;
  float vertices[m_MeshCount][vertexCount * indexCount];
  float _x[verticesForSquare] = {0.0f, factor, factor, factor, 0.0f, 0.0f};
  float _z[verticesForSquare] = {0.0f, 0.0f, factor, factor, factor, 0.0f};
  float textCoordX[] = {0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f};
  float textCoordY[] = {0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f};

  float paddingY = -(rowCount / 2.0f) * factor;
  size_t currentIndex = 0;
  /*
   *
  {0.0f, 0.05f, 0.05f, 0.05f, 0.0f, 0.0f};
  {0.0f, 0.0f, 0.05f, 0.05f, 0.05f, 0.0f};
   */
  float waterDepth = 0.01f;
  float waterWidth = 20.0f;
  float mountainHeight = 0.2f;
  float mountainWidth = 15.0f;
  float smooth = 0.08f;
  for(size_t meshIndex = 0; meshIndex < m_MeshCount; ++meshIndex){
    currentIndex = 0;
    for(int row=0; row<rowCount; row++){
      float paddingX = -(rowCount / 2.0f) * factor;
      for(int column=0; column<columnCount; column++){
        for(int index = 0; index<verticesForSquare; index++){
          vec3 pos = {_x[index] + paddingX, 0.0f, _z[index] + paddingY};
          glm::vec2 xy = glm::vec2(pos.x, pos.z);
          vec2 texture = {textCoordX[index], textCoordY[index]};
          vertices[meshIndex][currentIndex] = pos.x;
          vertices[meshIndex][currentIndex + 1] = smooth * (mountainWidth * glm::simplex(xy * mountainHeight) + waterWidth * glm::perlin(xy * waterDepth));
          vertices[meshIndex][currentIndex + 2] = pos.z;
          vertices[meshIndex][currentIndex + 3] = texture.x;
          vertices[meshIndex][currentIndex + 4] = texture.y;
          currentIndex+=indexCount;
        }
        paddingX += factor;
      }
      paddingY += factor;
    }
  }

  uint32_t indices[vertexCount];
  for(int i=0; i<vertexCount; ++i){
    indices[i] = i;
  }
  std::string pathAndName = fileName.substr(0, fileName.find(".obj"));
  for(size_t index = 0; index < m_MeshCount; ++index){
    std::string meshFileName = pathAndName + char(index + int('1') - 1) + ".obj";
    Engine::ObjFile::CreateObjFile(
      vertices[index],
      vertexCount,
      Engine::ObjFile::VertexCategory::VertexCategoryVertex | Engine::ObjFile::VertexCategory::VertexCategoryNormal,
      indexCount,
      indices,
      vertexCount,
      meshFileName
    );
  }
}
GameWorld::GameWorld()
: Layer("World"){
  std::string shaderFile = "sandbox/assets/shaders/World.glsl";
  std::string objFile = "sandbox/assets/models/World.obj";
  GenerateVertices(objFile);
  std::string pathAndName = objFile.substr(0, objFile.find(".obj"));
  for(size_t index = 0; index < m_MeshCount; ++index) {
    std::string meshFileName = pathAndName + char(index + int('1') - 1) + ".obj";
    m_Models.push_back(Engine::Mesh::Create(meshFileName, shaderFile));
  }
};
