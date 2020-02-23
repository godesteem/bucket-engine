/**
 * File              : OpenGLVertexArray.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 23.02.2020
 * Last Modified Date: 23.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once
#include "engine/renderer/VertexArray.h"


namespace Engine {
  
  class OpenGLVertexArray: public VertexArray
  {
  public:
    OpenGLVertexArray();
    ~OpenGLVertexArray() override;


    void Bind() const override;
    void Unbind() const override;

    void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
    void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
    //virtual void SetLayout(const BufferLayout& layout) override;
    virtual std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffer() override { return m_VertexBuffers;};
    virtual std::shared_ptr<IndexBuffer>& GetIndexBuffer() override { return m_IndexBuffer; };

  private:
    uint32_t m_RendererID = 0;
    std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
    std::shared_ptr<IndexBuffer> m_IndexBuffer;

  };

}
