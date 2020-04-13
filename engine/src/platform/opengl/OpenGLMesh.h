#pragma once

#include "engine/renderer/Mesh.h"
#include "engine/renderer/Texture.h"

namespace Engine {
  /**
   * OpenGL platform specific implementation of `Engine::Mesh`
   */
  class OpenGLMesh: public Mesh
  {
  public:
    /**
     * Constructor
     * @param objectFilePath file path to .obj file with mesh data
     * @param shaderFilePath file path to .glsl shader file
     * @param textureFilePath [optional] file path to texture in .jpg/.png format
     */
    OpenGLMesh(const std::string &objectFilePath, const std::string &shaderFilePath="", const std::string &textureFilePath="");

    /* TODO:
     *  - we need to be able to attach multiple shaders to a single mesh so passing a single file does not make any sense here.
     *  - replace vertexBuffer and indexBuffer with [vector/array] of VertexArrays
     */
    /**
     * Constructor
     * @param vertexBuffer
     * @param indexBuffer
     * @param shaderFile
     */
    OpenGLMesh(Ref<VertexBuffer>& vertexBuffer, const Ref<IndexBuffer>& indexBuffer, const std::string& shaderFile);

    /**
     * Copy constructor
     * @param mesh
     */
    explicit OpenGLMesh(const Ref<OpenGLMesh>& mesh);

    /**
     * Enables Mesh, including attached shaders/textures/vertex arrays and all relevant
     * steps performed to use the data with OpenGL
     */
    virtual void Bind() const override;

    /**
     * Disables Mesh
     */
    virtual void Unbind() const override;

    /**
     * OpenGL implementation of the update call for mesh,
     * move and draws the mesh
     * @param ts delta since last cycle
     */
    virtual void OnUpdate(Timestep ts) override;

    /**
     * Debugging window draw call
     */
    virtual void OnImGuiRender() override;

    // TODO: drop me.
    /**
     * setter for m_VertexArray.m_Size
     * @param size
     */
    virtual void SetVertexArraySize(uint32_t size) override;

    /**
     * Setter for debugging name
     * @param name
     */
    virtual void SetName(const std::string& name) override { m_Name = name; }

    /**
     * Copy operator
     * @param msh
     * @return
     */
    virtual OpenGLMesh& operator=(const OpenGLMesh& msh);

  private:

    /**
     * helper to read content of .glsl shader file into m_ShaderFileContent
     * @param shaderFilePath path to file
     * @return success
     */
    bool ExtractShaderFileContent(const std::string& shaderFilePath);

    /**
     * Reads data of .obj file into provided data structure
     * @param filePath path to .obj file
     * @param vertices container for vertex data
     * @param normals container for vertex normal data
     * @param uvs container for vertex texture UVs
     * @return success
     */
    static bool ReadObjFile(const std::string& filePath, std::vector<Engine::Math::vec3> &vertices, std::vector<Engine::Math::vec3> &normals, std::vector<Engine::Math::vec2> &uvs);

  private:

    // debugging helpers
    std::string m_Name; //! < debugging name
    std::string m_ShaderFileContent; //! < content of .glsl shader file

    Ref<VertexArray> m_VertexArray;

    ShaderLibrary m_ShaderLibrary; //! <container for shaders
    Ref<Texture2D> m_Texture; //! <mesh texture
    glm::vec3 m_Position = {0.0f, 0.0f, 0.0f}; //! <mesh position in world coordinates
  };
}
