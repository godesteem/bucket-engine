/**
 * File              : Mesh.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 01.03.2020
 * Last Modified Date: 23.03.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once
#include "engine/Core.h"
#include <glm/glm.hpp>
#include <utility>
#include <vector>
#include <regex>
#include "Buffer.h"
#include "VertexArray.h"
#include "engine/core/Timestep.h"
#include "Shader.h"
#include "OrthographicCamera.h"

#ifdef BE_PLATFORM_WINDOWS
  typedef unsigned short int ushort;
  typedef size_t ssize_t;
#endif

typedef ushort GLushort;

namespace Engine {
  struct ModelAttribute {
    std::string name;
    const VertexBuffer& buffer;

    ModelAttribute(std::string  n, const VertexBuffer& b)
    : name(std::move(n)), buffer(b)
    {}
  };
  class Mesh
  {
  public:
    virtual ~Mesh() = default;
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    virtual void OnUpdate(Timestep ts) = 0;
    virtual void OnImGuiRender() = 0;

    std::vector<ModelAttribute> GetAttributes () { return m_Attributes; };
    inline void SetAttribute(const std::string& key, const VertexBuffer& buffer) {
      m_Attributes.emplace_back(key, buffer);
    };

    static Ref<Mesh> Create(const std::string &objectFilePath, const std::string &shaderFilePath);
    static Ref<Mesh> Create(Ref<VertexBuffer>& vertexBuffer, Ref<IndexBuffer>& indexBuffer, const std::string& shaderFile);
    virtual void SetVertexArraySize(uint32_t size) = 0;
    virtual void SetName(const std::string& name) = 0;
    //static Ref<Mesh> Create(const std::string& filePath);
  protected:
    std::vector<ModelAttribute> m_Attributes;
  };
  struct ObjFile {
  public:

    enum VertexCategory {
      None = 0,
      VertexCategoryVertex = BIT(0),
      VertexCategoryUV = BIT(1),
      VertexCategoryNormal = BIT(2),
    };
    explicit ObjFile() {}

    explicit ObjFile(const std::string& fp);
    inline void Open(const char* mode="r") { file = fopen(filePath.c_str(), mode);}
    inline void Close() { fclose(file); file = nullptr;}
    inline bool IsOpen() { return file != nullptr; };
    inline std::vector<glm::vec3> GetVertices() const { return vertices; };
    inline std::vector<glm::vec3> GetNormals() const { return normals; };
    inline std::vector<glm::vec2> GetUVs() const { return uvs; };
    inline void SetFilePath(const std::string& fp) {filePath = fp;}
    inline void Write(const std::string& content) {
      if(!IsOpen()) Open("w");
      for(auto elem : content) putc(elem, file);
    }

    static void CreateObjFile(float* vertices, size_t vertexCount, uint32_t vertexCategories, size_t vertexElementCount, uint32_t* indices, size_t indexCount, const std::string& fp);;

    bool LoadObjFile(std::string const& fileName);

  private:
    FILE* file;
    std::string filePath;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;
    bool hasUVs = false, hasNormals = false;
  };
}
