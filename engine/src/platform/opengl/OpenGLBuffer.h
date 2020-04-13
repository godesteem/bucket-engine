#pragma once

#include "engine/renderer/Buffer.h"


namespace Engine {
  /**
   * OpenGL platform specific implementation of VertexBuffer.
   * A OpenGL vertex buffer can have several layouts
   * see https://stackoverflow.com/a/39684775/6904543
   */
  class OpenGLVertexBuffer : public VertexBuffer
  {
  public:
    /**
     * Constructor way3
     * @param vertices array with vertex data
     * @param size size of array `vertices`
     */
    OpenGLVertexBuffer(float* vertices, uint32_t size);

    /**
     * Constructor way1
     * @param vertices array with vertex data
     * @param verticeSize size of array `vertices`
     * @param normals array with vertex normal data
     * @param normalsSize size of array `normals`
     * @param textures array with vertex texture data
     * @param texturesSize size of array `textures`
     */
    OpenGLVertexBuffer(float* vertices, uint32_t verticeSize,
                       float* normals, uint32_t normalsSize,
                       float* textures, uint32_t texturesSize);

    /**
     * Destructor
     */
    virtual ~OpenGLVertexBuffer();

    /**
     * Binds OpenGL vertex buffer m_RendererIDs[0]
     * This is only for way3
     */
    virtual void Bind() const override;

    /**
     * Binds specific vertex buffer to current OpenGL context
     * This may only be used by way1 objects
     * @param index index of vertex buffer in m_RendererIDs
     */
    virtual void EnableBufferPart(size_t index) const override;

    /**
     * Binds Buffer 0 to OpenGL context (deactivates current active buffer)
     */
    virtual void Unbind() const override;

    /**
     * Setter for buffer layout
     * @param layout
     */
    virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };

    /**
     * Getter for buffer layout
     * @return current attached layout
     */
    virtual const BufferLayout& GetLayout() const override { return m_Layout; };

  private:
    uint32_t m_RendererIDs[3] = {0, 0, 0};
    BufferLayout m_Layout;
  };

  class OpenGLIndexBuffer : public IndexBuffer
  {
  public:
    OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
    virtual ~OpenGLIndexBuffer();

    virtual void Bind() const;
    virtual void Unbind() const;

    virtual uint32_t GetCount() const { return m_Count; }
  private:
    uint32_t m_RendererID;
    uint32_t m_Count;
  };

}
