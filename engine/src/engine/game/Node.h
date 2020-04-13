#pragma once
#include "Vertex.h"
#include <iostream>
#include <memory>

class Node
{
  Vertex _data;
  std::vector<std::weak_ptr<Node>> _neighbors;

public:
  Node(Vertex const& v)
    : _data(v)
  {
    std::cout << __FUNCTION__ << std::endl;
  }

  [[deprecated]] Node() { std::cout << __FUNCTION__ << std::endl; }

  bool addNeighbor(std::weak_ptr<Node> const& n)
  {
    if(n.expired())
      return false;

    //TODO check if valid, for example by distance between new nodes position and this position

    this->_neighbors.push_back(n);
    n.lock()->_neighbors.push_back(n);

    return true;
  }

  Vertex const& getVertex() { return _data; }
  Vertex const& setVertex(Vertex const& v) { return _data = v; }

  Vertex const& getVertex() const { return _data; }
  ~Node() { std::cout << __FUNCTION__ << std::endl; }
};
