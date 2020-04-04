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
  VertexBuffer* VertexBuffer::Create(const std::vector<glm::vec2> &vertices, uint32_t size) {
//    BE_CORE_ASSERT(size % 3 == 0, "Wrong vector size for vertices");
    float* _vertices = new float[size];
    int ind = 0;
    for (auto i : vertices) {
      _vertices[ind] = i.x;
      _vertices[ind + 1] = i.y;
      ind += 2;
    }
    auto a = Create(_vertices, size);
	delete[] _vertices;
	return a;
  }
  VertexBuffer* VertexBuffer::Create(const std::vector<glm::vec3> &vertices, uint32_t size){
//    BE_CORE_ASSERT(size % 3 == 0, "Wrong vector size for vertices");
	  float* _vertices = new float[size];
	  int ind = 0;
    for(auto i : vertices){
      _vertices[ind] = i.x;
      _vertices[ind+1] = i.y;
      _vertices[ind+2] = i.z;
      ind += 3;
    }
	auto a = Create(_vertices, size);
	delete[] _vertices;
	return a;
  }
  VertexBuffer* VertexBuffer::Create(const std::vector<glm::vec4> &vertices, uint32_t size){
    //BE_CORE_ASSERT(size % 4 == 0, "Wrong vector size for vertices");
	  float* _vertices = new float[size];
	  int ind = 0;
    for(auto i : vertices){
      _vertices[ind] = i.x;
      _vertices[ind+1] = i.y;
      _vertices[ind+2] = i.z;
      _vertices[ind+3] = i.w;
      ind += 4;
    }
	auto a = Create(_vertices, size);
	delete[] _vertices;
	return a;
  };
  IndexBuffer* IndexBuffer::Create(std::vector<unsigned short> indices, uint32_t size){
	  uint32_t* _indices = new uint32_t[size];
    for(int i = 0; i<size; ++i){
      _indices[i] = indices[i];
    }
	auto a = Create(_indices, size);
	delete[] _indices;
	return a;
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
