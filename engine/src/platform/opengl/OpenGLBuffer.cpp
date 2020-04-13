#include "bepch.h"
#include "OpenGLBuffer.h"
#include <glad/glad.h>

namespace Engine {

  /////////////////////////////////////////////////////////////////////////////
  // VertexBuffer /////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////

  OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
  {
    glGenBuffers(1, &m_RendererIDs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererIDs[0]);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
  }

  OpenGLVertexBuffer::~OpenGLVertexBuffer()
  {
    if (m_RendererIDs[1] != 0) {
      glDeleteBuffers(3, m_RendererIDs);
    } else {
      glDeleteBuffers(1, &m_RendererIDs[0]);
    }
  }

  void OpenGLVertexBuffer::Bind() const
  {
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererIDs[0]);
  }

  void OpenGLVertexBuffer::Unbind() const
  {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  /////////////////////////////////////////////////////////////////////////////
  // IndexBuffer //////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////

  OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
      : m_Count(count)
  {
    // TODO: This might be Platform dependent
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
  }

  OpenGLIndexBuffer::~OpenGLIndexBuffer()
  {
    glDeleteBuffers(1, &m_RendererID);
  }

  void OpenGLIndexBuffer::Bind() const
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
  }

  void OpenGLIndexBuffer::Unbind() const
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

}
