/**
 * File              : Buffer.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 22.02.2020
 * Last Modified Date: 01.03.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include "Buffer.h"
#include "Renderer.h"
#include "platform/opengl/OpenGLBuffer.h"

namespace Engine {
  VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size){
    switch(Renderer::GetAPI()){
      case RendererAPI::API::None: BE_CORE_ASSERT(false, "RendererAPI::None is currently not supported ");
      case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
    }
    BE_CORE_ASSERT(false, "Unknown RendererAPI");
    return nullptr;
  };
  VertexBuffer* VertexBuffer::Create(std::vector<glm::vec3> vertices, uint32_t size){
    BE_CORE_ASSERT(size % 3 == 0, "Wrong vector size for vertices");
    float _vertices[size];
    int ind = 0;
    for(auto i : vertices){
      _vertices[ind] = i.x;
      _vertices[ind+1] = i.y;
      _vertices[ind+2] = i.z;
      ind += 3;
    }
    return Create(_vertices, size);

  }
  VertexBuffer* VertexBuffer::Create(std::vector<glm::vec4> vertices, uint32_t size){
    BE_CORE_ASSERT(size % 4 == 0, "Wrong vector size for vertices");
    float _vertices[size];
    int ind = 0;
    for(auto i : vertices){
      _vertices[ind] = i.x;
      _vertices[ind+1] = i.y;
      _vertices[ind+2] = i.z;
      _vertices[ind+3] = i.w;
      ind += 4;
    }
    return Create(_vertices, size);
  };
  IndexBuffer* IndexBuffer::Create(std::vector<ushort> indices, uint32_t size){
    uint32_t _indices[size];
    for(int i = 0; i<size; ++i){
      _indices[i] = indices[i];
    }
    return Create(_indices, size);
  }
  IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size){
    switch(Renderer::GetAPI()){
      case RendererAPI::API::None: BE_CORE_ASSERT(false, "RendererAPI::None is currently not supported ");
      case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, size);
    }
    BE_CORE_ASSERT(false, "Unknown RendererAPI");
    return nullptr;
  };
};
