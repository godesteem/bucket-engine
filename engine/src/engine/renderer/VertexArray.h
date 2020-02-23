/**
 * File              : VertexArray.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 23.02.2020
 * Last Modified Date: 23.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once
#include <memory>
#include "Buffer.h"

namespace Engine {

  class VertexArray
  {
  public:
    virtual ~VertexArray() {};

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
    virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;
    //virtual void SetLayout(const BufferLayout& layout) = 0;
    //
    virtual std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffer() = 0;
    virtual std::shared_ptr<IndexBuffer>& GetIndexBuffer() = 0;

    static VertexArray* Create();
  };
}
