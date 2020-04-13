#pragma once
#include "math/matrix.h"

class Vertex
{
  Engine::Math::vec3 _pos;
  bool _isWalkable;

public:
  Vertex(Engine::Math::vec3 pos = { { 9999 }, { 9999 }, { 9999 } }, bool walkable = true)
    : _pos(pos)
    , _isWalkable(walkable)
  {
    std::cout << __FUNCTION__ << std::endl;
  }
  ~Vertex() { std::cout << __FUNCTION__ << std::endl; }
};
