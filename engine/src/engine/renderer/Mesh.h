#pragma once
#include "Buffer.h"
#include "OrthographicCamera.h"
#include "Shader.h"
#include "VertexArray.h"
#include "engine/Core.h"
#include "engine/core/Timestep.h"
#include "math/matrix.h"
#include <regex>
#include <utility>
#include <vector>

#ifdef BE_PLATFORM_WINDOWS
typedef unsigned short int ushort;
typedef size_t ssize_t;
#endif

typedef ushort GLushort;

namespace Engine
{
  class Mesh
  {
  public:
    virtual ~Mesh()                    = default;
    virtual void Bind() const          = 0;
    virtual void Unbind() const        = 0;
    virtual void OnUpdate(Timestep ts) = 0;
    virtual void OnImGuiRender()       = 0;

    static Ref<Mesh> Create(const std::string& objectFilePath, const std::string& shaderFilePath);
    static Ref<Mesh> Create(Ref<VertexBuffer>& vertexBuffer, Ref<IndexBuffer>& indexBuffer, const std::string& shaderFile);
    virtual void SetVertexArraySize(uint32_t size) = 0;
    virtual void SetName(const std::string& name)  = 0;
    //static Ref<Mesh> Create(const std::string& filePath);
  };
} // namespace Engine
