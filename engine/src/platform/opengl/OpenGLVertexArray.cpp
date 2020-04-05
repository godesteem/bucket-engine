#include "bepch.h"

#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace Engine {
  static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type){
    switch(type){
      case Engine::ShaderDataType::None: return GL_NONE;
      case Engine::ShaderDataType::Float: return GL_FLOAT;
      case Engine::ShaderDataType::Float2: return GL_FLOAT;
      case Engine::ShaderDataType::Float3: return GL_FLOAT;
      case Engine::ShaderDataType::Float4: return GL_FLOAT;
      case Engine::ShaderDataType::Int: return GL_INT;
      case Engine::ShaderDataType::Int2: return GL_INT;
      case Engine::ShaderDataType::Int3: return GL_INT;
      case Engine::ShaderDataType::Int4: return GL_INT;
      case Engine::ShaderDataType::Mat3: return GL_FLOAT;
      case Engine::ShaderDataType::Mat4: return GL_FLOAT;
      case Engine::ShaderDataType::Bool: return GL_BOOL;
    };
    BE_CORE_ASSERT(false, "ShaderDataType unknown.");
    return 0;
  }

    OpenGLVertexArray::OpenGLVertexArray(){
      // TODO: This might be Platform dependent
      glGenVertexArrays(1, &m_RendererID);
    }
    OpenGLVertexArray::~OpenGLVertexArray(){
      glDeleteVertexArrays(1, &m_RendererID);
    }
    void OpenGLVertexArray::Bind() const{
      glBindVertexArray(m_RendererID);
    }
    void OpenGLVertexArray::Unbind() const{
      glBindVertexArray(m_RendererID);
      for(size_t i = 0; i < m_VertexBuffersAttributesSize; ++i)
          glDisableVertexAttribArray(i);
      glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer){
      glBindVertexArray(m_RendererID);
      BE_CORE_ASSERT(m_RendererID, "VertexArray not bound.");
      vertexBuffer->Bind();

      BE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "VertexBuffer has no layout!");

      uint32_t index = m_VertexBuffersAttributesSize;
      const auto& layout = vertexBuffer->GetLayout();

      for(const auto& element: layout){
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(
          index,
          element.GetComponentCount(),
          ShaderDataTypeToOpenGLBaseType(element.Type),
          element.Normalized ? GL_TRUE : GL_FALSE,
          layout.GetStride(),
          (const void*) element.Offset
          //warning	c4312	'type cast': conversion from 'const uint32_t' to 'const void *' of greater size
        );
        index++;
      }
      m_VertexBuffersAttributesSize = index;
      m_VertexBuffers.push_back(vertexBuffer);
      for(size_t i = index; i > 0; --i)
        glDisableVertexAttribArray(i);
    }

    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer){
      glBindVertexArray(m_RendererID);
      BE_CORE_ASSERT(m_RendererID, "VertexArray not bound.");
      indexBuffer->Bind();

      m_IndexBuffer = indexBuffer;
    }

}
