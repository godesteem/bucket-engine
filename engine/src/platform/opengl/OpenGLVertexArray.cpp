/**
 * File              : OpenGLVertexArray.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 23.02.2020
 * Last Modified Date: 23.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */

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
    void OpenGLVertexArray::Bind() const{
      glBindVertexArray(m_RendererID);
    }
    void OpenGLVertexArray::Unbind() const{
      glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer){
      glBindVertexArray(m_RendererID);
      BE_CORE_ASSERT(m_RendererID, "VertexArray not bound.");
      vertexBuffer->Bind();

      BE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "VertexBuffer has no layout!");

      uint32_t index = 0;
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
        );
        index++;  
      }

      m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer){
      glBindVertexArray(m_RendererID);
      BE_CORE_ASSERT(m_RendererID, "VertexArray not bound.");
      indexBuffer->Bind();
      
      m_IndexBuffer = indexBuffer;
    }

}
