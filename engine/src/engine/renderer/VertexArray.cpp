#include "bepch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "platform/opengl/OpenGLVertexArray.h"

namespace Engine {
  VertexArray* VertexArray::Create(){
    switch(Renderer::GetAPI()){
      case RendererAPI::API::None: BE_CORE_ASSERT(false, "RendererAPI::None is currently not supported ");
      case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
    }
    BE_CORE_ASSERT(false, "Unknown RendererAPI");
    return nullptr; 
  }
}
