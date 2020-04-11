#include "GameWorld.h"
#include <math/matrix.h>

GameWorld::GameWorld(Engine::Ref<Engine::VertexBuffer> vb, Engine::Ref<Engine::IndexBuffer> ib, const std::string& name)
  : Layer(name)
{
  m_Mesh = Engine::Mesh::Create(vb, ib, "sandbox/assets/shaders/World.glsl");
}

void GameWorld::OnImGuiRender()
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

void GameWorld::GenerateVertices(const std::string& fileName)
{
  // Warning	C6262	Function uses '921780' bytes of stack:  exceeds /analyze:stacksize '16384'.  Consider moving some data to heap.

  const int rowCount = 80;
  const int columnCount = rowCount;
  const int verticesForSquare = 6;
  const int vertexCount = verticesForSquare * rowCount * columnCount;
  const int indexCount = 5;
  float factor = 1.0f;
  float vertices[vertexCount * indexCount];
  float _x[verticesForSquare] = { 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f };
  float _z[verticesForSquare] = { 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f };
  float textCoordX[] = { 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f };
  float textCoordY[] = { 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f };

  float paddingY = 0.0f;
  size_t currentIndex = 0;

  for (int row = 0; row < rowCount; row++)
  {
    float paddingX = -(rowCount / 2.0f) * factor;
    for (int column = 0; column < columnCount; column++)
    {
      for (int index = 0; index < verticesForSquare; index++)
      {
        Engine::Math::vec3 pos{ { _x[index] + paddingX },{ 0.0f },{ _z[index] + paddingY } };

        Engine::Math::vec2 texture{ { textCoordX[index] },{ textCoordY[index] } };
        vertices[currentIndex] = pos.x();
        vertices[currentIndex + 1] = 10.0f * sinf(10 * (pos.x() * pos.x() + pos.z() * pos.z())) / 10;
        vertices[currentIndex + 2] = pos.z();
        vertices[currentIndex + 3] = texture.x();
        vertices[currentIndex + 4] = texture.y();
        currentIndex += indexCount;
      }
      paddingX += factor;
    }
    paddingY += factor;
  }

  uint32_t indices[vertexCount];
  for (int i = 0; i < vertexCount; ++i) { indices[i] = i; }

  Engine::ObjFile::CreateObjFile(
    vertices, vertexCount, Engine::ObjFile::VertexCategory::VertexCategoryVertex | Engine::ObjFile::VertexCategory::VertexCategoryNormal, indexCount, indices, vertexCount, fileName);
}
