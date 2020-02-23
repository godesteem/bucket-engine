/**
 * File              : Buffer.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 22.02.2020
 * Last Modified Date: 23.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include "Buffer.h"
#include "Renderer.h"
#include "platform/opengl/OpenGLBuffer.h"

namespace Engine {
  VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size){
    switch(Renderer::GetAPI()){
      case RendererAPI::None: BE_CORE_ASSERT(false, "RendererAPI::None is currently not supported ");
      case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
    }
    BE_CORE_ASSERT(false, "Unknown RendererAPI");
    return nullptr;
  };

  IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size){
    switch(Renderer::GetAPI()){
      case RendererAPI::None: BE_CORE_ASSERT(false, "RendererAPI::None is currently not supported ");
      case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, size);
    }
    BE_CORE_ASSERT(false, "Unknown RendererAPI");
    return nullptr;
  };
};
