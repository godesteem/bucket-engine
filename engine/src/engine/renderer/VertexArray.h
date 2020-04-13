#pragma once
#include <memory>
#include "engine/Core.h"
#include "Buffer.h"

namespace Engine {

  /**
   * Stores information about vertices,
   * this can be a combination of sorted vertex buffers
   * or a vertex buffer in combination with a index buffer
   */
  class VertexArray
  {
  public:
    virtual ~VertexArray() {};

    /**
     * static constructor
     * @return VertexArray object
     */
    static VertexArray* Create();

    virtual std::vector<Ref<VertexBuffer>>& GetVertexBuffer() = 0;

    /**
     * Getter for index buffer
     * @return attached IndexBuffer
     */
    virtual Ref<IndexBuffer>& GetIndexBuffer() = 0;

    /**
     * Getter for array size
     * @return current size
     */
    inline uint32_t GetSize() const { return m_Size; };

    /**
     * Setter for IndexBuffer
     * @param indexBuffer IndexBuffer to attach
     */
    virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

    /**
     * Setter for array size
     * @param size
     */
    inline void SetSize(uint32_t size) { m_Size = size; };

    /**
     * Add a vertex buffer to the vertex array
     * @param vertexBuffer VertexBuffer to attach
     */
    virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;

    /**
     * Enables VertexArray
     */
    virtual void Bind() const = 0;

    /**
     * Disables VertexArray
     */
    virtual void Unbind() const = 0;

  protected:
    uint32_t m_Size = 0; //! <Buffer size
  };
}
