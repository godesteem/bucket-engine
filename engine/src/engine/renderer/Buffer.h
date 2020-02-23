/**
 * File              : Buffer.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 22.02.2020
 * Last Modified Date: 22.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once

namespace Engine {
  class VertexBuffer
  {
  public:
    virtual ~VertexBuffer() {};

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    static VertexBuffer* Create(float* vertices, uint32_t size);
  };

  class IndexBuffer {
  public:
    virtual ~IndexBuffer() {};
    
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual uint32_t GetCount() const = 0;

    static IndexBuffer* Create(uint32_t* indices, uint32_t count);

  };
}
