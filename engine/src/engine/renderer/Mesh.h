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

    /**
     * Enables Mesh, including activating data for rendering
     */
    virtual void Bind() const          = 0;

    /**
     * Disables Mesh
     */
    virtual void Unbind() const        = 0;

    /**
     * Updates and draws mesh
     * @param ts delta since the last cycle
     */
    virtual void OnUpdate(Timestep ts) = 0;

    /**
     * Draw function for debug interface
     */
    virtual void OnImGuiRender()       = 0;

    /**
     * Static constructor
     * @param objectFilePath file path to .obj file with Mesh data
     * @param shaderFilePath file path to shader file with Shader data
     * @return reference to Mesh object
     */
    static Ref<Mesh> Create(const std::string& objectFilePath, const std::string& shaderFilePath);

    /**
     * Static constructor
     * @param vertexBuffer
     * @param indexBuffer
     * @param shaderFile
     * @return reference to Mesh object
     */
    static Ref<Mesh> Create(Ref<VertexBuffer>& vertexBuffer, Ref<IndexBuffer>& indexBuffer, const std::string& shaderFile);

    /**
     * Setter for m_VertexArray.m_Size
     * @param size
     */
    virtual void SetVertexArraySize(uint32_t size) = 0;

    /**
     * Setter for debugging name
     * @param name
     */
    virtual void SetName(const std::string& name)  = 0;
  };
} // namespace Engine
