/**
 * File              : Mesh.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 01.03.2020
 * Last Modified Date: 09.03.2020
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

    explicit ObjFile(const std::string& fp)
        :filePath(CONSTRUCT_FILE_PATH(fp)),
         file(nullptr) {
      /*
       * Loads a .obj file with following layout
       * vertices    : v %f %f %f
       * uvs         : vt %f %f
       * normals     : vn %f %f %f
       * figure faces:
       * syntax: <v>/<vt>/<vn> || <v> || <v>//<vn>
       * f %d %d %d
       * f %d//%d %d//%d %d//%d
       * f %d/%d/%d %d/%d/%d %d/%d/%d
       */
      std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
      std::vector<glm::vec3> temp_vertices;
      std::vector<glm::vec2> temp_uvs;
      std::vector<glm::vec3> temp_normals;

      char *line_buf = NULL;
      size_t line_buf_size = 0;
      ssize_t line_size;
      Open("r");
      if (!IsOpen()) {
        // Do sth
        BE_CORE_ASSERT(false, "File " + fp + " can not be opened.");
      }
      line_size = getline(&line_buf, &line_buf_size, file);
      std::regex txt_regex("[a-z]*");
      while (line_size >= 0) {
        std::string line(line_buf);
        std::string prefix;
        std::stringstream ss(line);

        ss >> prefix;
        ss.ignore(1, ' ');
        if(prefix == "v"){
          glm::vec3 vertex;
          ss >> vertex.x;
          ss.ignore(1, ' ');
          ss >> vertex.y;
          ss.ignore(1, ' ');
          ss >> vertex.z;
          temp_vertices.push_back(vertex);
        } else if(prefix == "vt"){
          // UVs
          glm::vec2 uv;
          ss >> uv.x;
          ss.ignore(1, ' ');
          ss >> uv.y;
          uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
          temp_uvs.push_back(uv);
        } else if(prefix == "vn"){
          // Normals
          glm::vec3 normal;
          ss >> normal.x;
          ss.ignore(1, ' ');
          ss >> normal.y;
          ss.ignore(1, ' ');
          ss >> normal.z;
          temp_normals.push_back(normal);
        } else if (prefix == "f") {
          // Figure faces (combination of indices to construct the object)
          std::string vertex1, vertex2, vertex3;
          unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
          if(line.find("//") != -1 ) {
            for (int i = 0; i < 3; ++i) {
              ss >> vertexIndex[i];
              ss.ignore(2, '/');
              ss >> normalIndex[i];
              if (i < 2) ss.ignore(1, ' ');
            }
            hasNormals = true;
          }
          else if (line.find('/') != -1) {
            for (int i = 0; i < 3; ++i) {
              ss >> vertexIndex[i];
              ss.ignore(1, '/');
              ss >> uvIndex[i];
              ss.ignore(1, '/');
              ss >> normalIndex[i];
              if (i < 2) ss.ignore(1, ' ');
            }
            hasUVs = true;
            hasNormals = true;
          } else if (line.find('/') == -1){
            for(int i=0; i<3;++i) {
              ss >> vertexIndex[i];
              if(i<2) ss.ignore(1, ' ');
            }
          }
          for(int i = 0; i<3; ++i) {
            vertexIndices.push_back(vertexIndex[i]);
            if (hasUVs) {
              uvIndices.push_back(uvIndex[i]);
            }
            if (hasNormals) {
              normalIndices.push_back(normalIndex[i]);
            }
          }
        }
        line_size = getline(&line_buf, &line_buf_size, file);
      }
      Close();
      int correction = 1;

      // For each vertex of each triangle
      for (unsigned int i = 0; i < vertexIndices.size(); i++) {
        if (!temp_vertices.empty() && !vertexIndices.empty()) {
          unsigned int vertexIndex = vertexIndices[i];
          for(auto index : vertexIndices){
            if(index == 0)
              correction = 0;
          }
          glm::vec3 vertex = temp_vertices[vertexIndex - correction];
          vertices.push_back(vertex);
        }
        if (!temp_uvs.empty() && !uvIndices.empty()) {
          unsigned int uvIndex = uvIndices[i];
          glm::vec2 uv = temp_uvs[uvIndex - correction];
          uvs.push_back(uv);
        }
        if (!temp_normals.empty() && !normalIndices.empty()) {
          unsigned int normalIndex = normalIndices[i];
          glm::vec3 normal = temp_normals[normalIndex - correction];
          normals.push_back(normal);
        }
      }
    }
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

    static void CreateObjFile(float* vertices, size_t vertexCount, uint32_t vertexCategories, size_t vertexElementCount, uint32_t* indices, size_t indexCount, const std::string& fp){
      ObjFile file;
      file.SetFilePath(CONSTRUCT_FILE_PATH(fp));
      std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
      std::vector<glm::vec3> temp_vertices;
      std::vector<glm::vec2> temp_uvs;
      std::vector<glm::vec3> temp_normals;

      char *line_buf = NULL;
      size_t line_buf_size = 0;
      ssize_t line_size;
      file.Open("w");
      if (!file.IsOpen()) {
        // Do sth
        BE_CORE_ASSERT(false, "File " + fp + " can not be opened.");
      }
      std::ostringstream vertexStream, uvStream, normalStream, faceStream;
      for (size_t index = 0; index<vertexCount; ++index) {
        size_t realIndex = index * vertexElementCount;
        if (vertexCategories & VertexCategory::VertexCategoryVertex) {
          vertexStream << "v ";
          vertexStream << vertices[realIndex];
          vertexStream << " ";
          vertexStream << vertices[realIndex + 1];
          vertexStream << " ";
          vertexStream << vertices[realIndex + 2];
          vertexStream << "\n";
        }
        if (vertexCategories & VertexCategory::VertexCategoryUV) {
          uvStream << "vt ";
          uvStream << vertices[realIndex + 3];
          uvStream << " ";
          uvStream << vertices[realIndex + 4];
          uvStream << "\n";
        }
        if (vertexCategories & VertexCategory::VertexCategoryNormal) {
          normalStream << "vn ";
          normalStream << vertices[realIndex + 5];
          normalStream << " ";
          normalStream << vertices[realIndex + 6];
          normalStream << "\n";
        }
      }
      for(size_t index=0; index<indexCount;++index) {
        if(index%3==0) faceStream << "f ";
        faceStream << index;
        if(index%3==2) faceStream << "\n";
        else faceStream << " ";
      }
      file.Write("# auto generated file\n");
      file.Write("# " + fp + "\n");
      file.Write(vertexStream.str());
      file.Write(normalStream.str());
      file.Write(faceStream.str());
      file.Close();
    };

  private:
    FILE* file;
    std::string filePath;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;
    bool hasUVs = false, hasNormals = false;
  };
}
