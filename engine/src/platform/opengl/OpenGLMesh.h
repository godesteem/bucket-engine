/**
 * File              : OpenGLMesh.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 01.03.2020
 * Last Modified Date: 01.03.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once

#include "engine/renderer/Mesh.h"
#include "engine/renderer/Texture.h"
#include <regex>

namespace Engine {
  class OpenGLMesh: public Mesh
  {
  friend Mesh;
  public:
    OpenGLMesh(const std::string &objectFilePath, const std::string &shaderFilePath="", const std::string &textureFilePath="");
    OpenGLMesh(Ref<VertexBuffer>& vertexBuffer, const Ref<IndexBuffer>& indexBuffer, const std::string& shaderFile);
    explicit OpenGLMesh(const Ref<OpenGLMesh>& mesh);
    virtual void Bind() const override;
    virtual void Unbind() const override;
    virtual void OnUpdate(Timestep ts) override;
    virtual void OnImGuiRender() override;
    virtual void SetVertexArraySize(uint32_t size) override;
    virtual OpenGLMesh& operator=(const OpenGLMesh& msh);

  private:
    static bool ReadObjFile(const std::string& filePath, std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, std::vector<glm::vec2> &uvs);
  private:
    std::string m_Name;
    Ref<VertexBuffer> m_VertexBuffer;
    Ref<VertexArray> m_VertexArray;
    ShaderLibrary m_ShaderLibrary;
    Ref<Texture2D> m_Texture;
    glm::vec3 m_Position = {1.0f, 1.0f, 1.0f};
    std::string m_ShaderFileContent;
  };
  struct ObjFile {
  public:
    explicit ObjFile(const std::string& fp)
    :filePath(fp),
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

      // For each vertex of each triangle
      for (unsigned int i = 0; i < vertexIndices.size(); i++) {
        if (!temp_vertices.empty()) {
          unsigned int vertexIndex = vertexIndices[i];
          glm::vec3 vertex = temp_vertices[vertexIndex - 1];
          vertices.push_back(vertex);
        }
        if (!temp_uvs.empty()) {
          unsigned int uvIndex = uvIndices[i];
          glm::vec2 uv = temp_uvs[uvIndex - 1];
          uvs.push_back(uv);
        }
        if (!temp_normals.empty()) {
          unsigned int normalIndex = normalIndices[i];
          glm::vec3 normal = temp_normals[normalIndex - 1];
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

  private:
    FILE* file;
    const std::string& filePath;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;
    bool hasUVs = false, hasNormals = false;
  };
}
