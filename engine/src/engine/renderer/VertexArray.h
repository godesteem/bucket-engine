#pragma once
#include <memory>
#include "engine/core/Core.h"
#include "Buffer.h"

namespace Engine {

  class VertexArray
  {
  public:
    virtual ~VertexArray() {};

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
    virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;
    //virtual void SetLayout(const BufferLayout& layout) = 0;
    //
    virtual std::vector<Ref<VertexBuffer>>& GetVertexBuffer() = 0;
    virtual Ref<IndexBuffer>& GetIndexBuffer() = 0;

    static VertexArray* Create();
    inline uint32_t GetSize() const { return m_Size; };
    inline void SetSize(uint32_t s) { m_Size = s; };

  protected:
    uint32_t m_Size = 0;
  };
}
