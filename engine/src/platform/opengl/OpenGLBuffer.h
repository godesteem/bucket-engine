/**
 * File              : OpenGLBuffer.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 22.02.2020
 * Last Modified Date: 23.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once

#include "engine/renderer/Buffer.h"


namespace Engine {
  class OpenGLVertexBuffer : public VertexBuffer
  {
  public:
    OpenGLVertexBuffer(float* vertices, uint32_t size);
    virtual ~OpenGLVertexBuffer();

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };
    virtual const BufferLayout& GetLayout() const override { return m_Layout; };
  private:
    uint32_t m_RendererID;
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
