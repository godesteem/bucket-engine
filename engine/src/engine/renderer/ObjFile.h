//
// Created by philipp on 12.04.20.
//
#pragma once

#include <regex>
#include <utility>
#include <vector>
#include "Buffer.h"
#include "OrthographicCamera.h"
#include "Shader.h"
#include "VertexArray.h"
#include "engine/Core.h"
#include "engine/core/Timestep.h"
#include "math/matrix.h"


namespace Engine {
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
    inline const std::vector<face>& GetFaces() const { return _faces; };
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
    bool _hasTextures     = false;
    bool _hasNormals = false;
  };

  ENABLE_BITMASK_OPERATORS(ObjFile::VertexCategory)

}