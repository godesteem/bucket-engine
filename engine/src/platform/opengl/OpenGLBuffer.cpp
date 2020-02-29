/**
 * File              : OpenGLBuffer.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 22.02.2020
 * Last Modified Date: 23.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include "bepch.h"
#include "OpenGLBuffer.h"
#include <glad/glad.h>

namespace Engine {

  /////////////////////////////////////////////////////////////////////////////
  // VertexBuffer /////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////

  OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
  {
    BE_CORE_TRACE("Creating OpenGLVertexBuffer");
    // TODO: This might be Platform dependent
    glGenBuffers(1, &m_RendererID);
    BE_CORE_TRACE("Binding OpenGLVertexBuffer.");
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    BE_CORE_TRACE("Setting OpenGLVertexBuffer data.");
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    BE_CORE_TRACE("OpenGLVertexBuffer creation done.");
  }

  OpenGLVertexBuffer::~OpenGLVertexBuffer()
  {
    glDeleteBuffers(1, &m_RendererID);
  }

  void OpenGLVertexBuffer::Bind() const
  {
    BE_CORE_TRACE("Binding OpenGLVertexBuffer");
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
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