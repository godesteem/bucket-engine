/**
 * File              : OpenGLVertexArray.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 23.02.2020
 * Last Modified Date: 25.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once
#include "engine/core/Core.h"
#include "engine/renderer/VertexArray.h"


namespace Engine {

  class OpenGLVertexArray: public VertexArray
  {
  public:
    OpenGLVertexArray();
    ~OpenGLVertexArray() override;


    void Bind() const override;
    void Unbind() const override;

    void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
    void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;
    //virtual void SetLayout(const BufferLayout& layout) override;
    virtual std::vector<Ref<VertexBuffer>>& GetVertexBuffer() override { return m_VertexBuffers;};
    virtual Ref<IndexBuffer>& GetIndexBuffer() override { return m_IndexBuffer; };

  private:
    uint32_t m_RendererID = 0;
    std::vector<Ref<VertexBuffer>> m_VertexBuffers;
    Ref<IndexBuffer> m_IndexBuffer;
    uint32_t m_VertexBuffersAttributesSize = 0;
  };

}
