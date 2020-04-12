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
  struct ModelAttribute
  {
    std::string name;
    const VertexBuffer& buffer;

    ModelAttribute(std::string n, const VertexBuffer& b)
      : name(std::move(n))
      , buffer(b)
    { }
  };
  class Mesh
  {
  public:
    virtual ~Mesh()                    = default;
    virtual void Bind() const          = 0;
    virtual void Unbind() const        = 0;
    virtual void OnUpdate(Timestep ts) = 0;
    virtual void OnImGuiRender()       = 0;

    std::vector<ModelAttribute> GetAttributes() { return m_Attributes; };
    inline void SetAttribute(const std::string& key, const VertexBuffer& buffer) { m_Attributes.emplace_back(key, buffer); };

    static Ref<Mesh> Create(const std::string& objectFilePath, const std::string& shaderFilePath);
    static Ref<Mesh> Create(Ref<VertexBuffer>& vertexBuffer, Ref<IndexBuffer>& indexBuffer, const std::string& shaderFile);
    virtual void SetVertexArraySize(uint32_t size) = 0;
    virtual void SetName(const std::string& name)  = 0;
    //static Ref<Mesh> Create(const std::string& filePath);
  protected:
    std::vector<ModelAttribute> m_Attributes;
  };


  struct ObjFile
  {
  public:
    enum class VertexCategory
    {
      None   = 0,
      Vertex = BIT(0),
      UV     = BIT(1),
      Normal = BIT(2),
    };

    struct facePart
    {
      // <0 is an illegal value, hence when 0 appears it means nothing was in the file
      size_t vertex = 0;
      size_t texture = 0;
      size_t normal = 0;
      friend std::ostream& operator<<(std::ostream& ostr, facePart const& fp)
      {
        ostr << fp.vertex;
        ostr << '/';
        if(fp.texture != 0) ostr << fp.texture;
        ostr << '/';
        if(fp.normal != 0) ostr << fp.normal;
        return ostr;
      }
    };

    struct face
    {
      facePart p1;
      facePart p2;
      facePart p3;
    };

    explicit ObjFile() { }

    explicit ObjFile(const std::string& fp);
    ~ObjFile();

    inline const std::vector<Engine::Math::vec3>& GetVertices() const { return _vertices; };
    inline const std::vector<Engine::Math::vec3>& GetNormals() const { return _normals; };
    inline const std::vector<Engine::Math::vec2>& GetTextureUVs() const { return _texture_uvs; };
    inline const std::string& SetFilePath(const std::string& fp) { return _filePath = fp; }
    inline const std::string& GetFilePath() { return _filePath; }
    static void CreateObjFile(float* vertices, size_t vertexCount, VertexCategory vertexCategories, size_t vertexElementCount, uint32_t* indices, size_t indexCount, const std::string& fp);

    /**
     * loads other content into this objfile's memory
     * @param fileName: target file name
     * @return success
     */
    bool LoadObjFile(std::string const& fileName);

    /**
     * saves file to other filepath
     * @param fileName: target file name
     * @return success
     */
    bool saveObjFile(std::string const& fileName);

    /**
     * saves current content into filepath
     * @return success
     */
    bool saveObjFile() { return saveObjFile(this->_filePath); }

  private:
    std::string _filePath;
    std::vector<Engine::Math::vec3> _vertices;
    std::vector<Engine::Math::vec3> _normals;
    std::vector<Engine::Math::vec2> _texture_uvs;
    std::vector<face> _faces;
    bool _hasTexturess     = false;
    bool _hasNormals = false;
  };
  ENABLE_BITMASK_OPERATORS(ObjFile::VertexCategory);
} // namespace Engine
