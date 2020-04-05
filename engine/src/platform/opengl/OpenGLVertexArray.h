#pragma once
#include "engine/Core.h"
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
