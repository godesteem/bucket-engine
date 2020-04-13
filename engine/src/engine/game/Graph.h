#pragma once
#include <iostream>
#include <memory>

#include "Node.h"
#include "Vertex.h"

namespace Engine::Map
{
  class Graph
  {
    std::vector<std::shared_ptr<Node>> _nodes; // TODO make this a bsp if finding a node is too slow

  public:
    Graph() { std::cout << __FUNCTION__ << std::endl; }

    void addVertex(Vertex const& v)
    {
      std::cout << __FUNCTION__ << std::endl;
      std::unique_ptr<Node> newNode(new Node(v));
      //TODO add node neighbors
      this->_nodes.push_back(std::move(newNode));
    }

    std::vector<std::weak_ptr<Vertex>> getPath(Engine::Math::vec3 const& start, Engine::Math::vec3 const& end) const
    {
      //TODO
      // find closest vertex node to start/end then path between

      return std::vector<std::weak_ptr<Vertex>>();
    }

    ~Graph() { std::cout << __FUNCTION__ << std::endl; }
  };

} // namespace Engine::Map
