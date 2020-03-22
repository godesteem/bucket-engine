/**
 * File              : Mesh.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 01.03.2020
 * Last Modified Date: 01.03.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include "Mesh.h"
#include "Renderer.h"
#include "platform/opengl/OpenGLMesh.h"
#include <fstream>

namespace Engine {
  Ref<Mesh> Mesh::Create(const std::string &objectFilePath, const std::string &shaderFilePath) {
    switch(Renderer::GetAPI()){
      case RendererAPI::API::None: BE_CORE_ASSERT(false, "RendererAPI::None is currently not supported ");
      case RendererAPI::API::OpenGL: return std::make_shared<OpenGLMesh>(objectFilePath, shaderFilePath);
    }
    BE_CORE_ASSERT(false, "Unknown RendererAPI");
    return nullptr;

  }

  Ref<Mesh> Mesh::Create(Ref<VertexBuffer>& vertexBuffer, Ref<IndexBuffer>& indexBuffer, const std::string& shaderFile) {
    switch(Renderer::GetAPI()){
      case RendererAPI::API::None: BE_CORE_ASSERT(false, "RendererAPI::None is currently not supported ");
      case RendererAPI::API::OpenGL: return std::make_shared<OpenGLMesh>(vertexBuffer, indexBuffer, shaderFile);
    }
    BE_CORE_ASSERT(false, "Unknown RendererAPI");
    return nullptr;
  }

  ObjFile::ObjFile(const std::string& fp)
    : filePath(CONSTRUCT_FILE_PATH(fp))
    , file(nullptr)
  {
    loadFromOBJfileOLD(this->filePath);
    loadFromOBJfile(this->filePath);
  }

  bool ObjFile::loadFromOBJfileOLD(std::string const& fileName)
  {
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

    char* line_buf = NULL;
    size_t line_buf_size = 0;
    ssize_t line_size;
    Open("r");
    if (!IsOpen()) {
      // Do sth
      BE_CORE_ASSERT(false, std::string() + __FUNCTION__ + " File " + fileName + " can not be opened.");
      return false;
    }

    line_size = getline_NERV(&line_buf, &line_buf_size, file);
    //  std::regex txt_regex("[a-z]*");
    while (line_size >= 0 && line_size != std::string::npos) {
      std::string line(line_buf);
      std::string prefix;
      std::stringstream ss(std::string() + line_buf);

      ss >> prefix;
      ss.ignore(1, ' ');
      if (prefix == "v") {
        glm::vec3 vertex;
        ss >> vertex.x;
        ss.ignore(1, ' ');
        ss >> vertex.y;
        ss.ignore(1, ' ');
        ss >> vertex.z;
        temp_vertices.push_back(vertex);
      }
      else if (prefix == "vt") {
        // UVs
        glm::vec2 uv;
        ss >> uv.x;
        ss.ignore(1, ' ');
        ss >> uv.y;
        uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
        temp_uvs.push_back(uv);
      }
      else if (prefix == "vn") {
        // Normals
        glm::vec3 normal;
        ss >> normal.x;
        ss.ignore(1, ' ');
        ss >> normal.y;
        ss.ignore(1, ' ');
        ss >> normal.z;
        temp_normals.push_back(normal);
      }
      else if (prefix == "f") {
        // Figure faces (combination of indices to construct the object)
        std::string vertex1, vertex2, vertex3;
        unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
        if (line.find("//") != std::string::npos) {
          for (int i = 0; i < 3; ++i) {
            ss >> vertexIndex[i];
            ss.ignore(2, '/');
            ss >> normalIndex[i];
            if (i < 2) ss.ignore(1, ' ');
          }
          hasNormals = true;
        }
        else if (line.find('/') != std::string::npos) {
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
        }
        else if (line.find('/') == std::string::npos) {
          for (int i = 0; i<3; ++i) {
            ss >> vertexIndex[i];
            if (i<2) ss.ignore(1, ' ');
          }
        }
        for (int i = 0; i<3; ++i) {
          vertexIndices.push_back(vertexIndex[i]);
          if (hasUVs) {
            uvIndices.push_back(uvIndex[i]);
          }
          if (hasNormals) {
            normalIndices.push_back(normalIndex[i]);
          }
        }
      }
      line_size = getline_NERV(&line_buf, &line_buf_size, file);
    }
    Close();
    int correction = 1;

    // For each vertex of each triangle
    for (unsigned int i = 0; i < vertexIndices.size(); i++) {
      if (!temp_vertices.empty() && !vertexIndices.empty()) {
        unsigned int vertexIndex = vertexIndices[i];
        for (auto index : vertexIndices) {
          if (index == 0)
          {
            correction = 0;
            break;
          }
        }
        glm::vec3 vertex = temp_vertices[vertexIndex - correction];
        this->vertices.push_back(vertex);
      }
      if (!temp_uvs.empty() && !uvIndices.empty()) {
        unsigned int uvIndex = uvIndices[i];
        glm::vec2 uv = temp_uvs[uvIndex - correction];
        this->uvs.push_back(uv);
      }
      if (!temp_normals.empty() && !normalIndices.empty()) {
        unsigned int normalIndex = normalIndices[i];
        glm::vec3 normal = temp_normals[normalIndex - correction];
        this->normals.push_back(normal);
      }
    }
    return true;
  }

  void ObjFile::CreateObjFile(float * vertices, size_t vertexCount, uint32_t vertexCategories, size_t vertexElementCount, uint32_t * indices, size_t indexCount, const std::string & fp) {
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
    for (size_t index = 0; index<indexCount; ++index) {
      if (index % 3 == 0) faceStream << "f ";
      faceStream << index;
      if (index % 3 == 2) faceStream << "\n";
      else faceStream << " ";
    }
    file.Write("# auto generated file\n");
    file.Write("# " + fp + "\n");
    file.Write(vertexStream.str());
    file.Write(normalStream.str());
    file.Write(faceStream.str());
    file.Close();
  }

  bool ObjFile::loadFromOBJfile(std::string const& fileName)
  {
  /* */
    std::ifstream fin(fileName);

    if (!fin)
    {
      BE_CORE_ASSERT(false, std::string() + __FUNCTION__ + " File " + fileName + " can not be opened.");
      fin.close();
      return false;
    }
    //    std::streampos p = fin.tellg();
    //    std::stringstream ss;
    //    ss << fin.rdbuf();
    //    fin.seekg(p);

    std::vector<glm::vec3> vertices;
    vertices.push_back(glm::vec3()); // offset as file is 1-indexed

    std::vector<glm::vec2> verticesTexture;
    verticesTexture.push_back(glm::vec2()); // offset

                                                    // test
    while(!fin.eof())
    {
      std::string currentLine;
      std::getline(fin, currentLine);
      switch (currentLine[0])
      {
      case '#':
        // comment, ignore line
        break;

      case 'v':
        // line may contain a vertex
      {
        currentLine.erase(0, 1);
        char vertexKind = currentLine[0];
        if ( vertexKind != ' ' // geometric
          && vertexKind != 't' // texture
          && vertexKind != 'n' // normal
          && vertexKind != 'p' // parameter space
          )
        {
          // unrecognized vertex specifier, ignore line
          break;
        }
        //            currentLine.erase(0, 1);

        size_t start0 = currentLine.find_first_of(' ');
        size_t end0   = currentLine.find_first_of(' ', start0+1);
        size_t start1 = currentLine.find_first_of(' ', end0);
        size_t end1   = currentLine.find_first_of(' ', start1+1);
        size_t start2 = currentLine.find_first_of(' ', end1);
        size_t end2   = currentLine.find_first_of(' ', start2+1);

        switch (vertexKind)
        {
        case ' ':
          // geometric vertex
        {
          float x = 0, y = 0, z = 0;

          if(start0 != std::string::npos && start0 < currentLine.size())
            try {
            x = stof(currentLine.substr(start0, end0 - start0));
          } catch (...) { }

          if (start1 != std::string::npos && start1 < currentLine.size())
            try {
            y = stof(currentLine.substr(start1, end1 - start1));
          }catch (...) { }

          if (start2 != std::string::npos && start2 < currentLine.size())
            try {
            z = stof(currentLine.substr(start2, end2 - start2));
          }catch (...) { }

          glm::vec3 v(x, y, z);
          vertices.push_back(v);
          break;
        }
        case 't':
          // texture vertex
        {
          float x = 0, y = 0;

          if(start0 != std::string::npos && start0 < currentLine.size())
            try {
            x = stof(currentLine.substr(start0, end0 - start0));
          } catch (...) { }

          if (start1 != std::string::npos && start1 < currentLine.size())
            try {
            y = stof(currentLine.substr(start1, end1 - start1));
          }catch (...) { }

          glm::vec2 v(x, y);
          verticesTexture.push_back(v);
          break;
        }
        default: // dont handle anything else
          break;
        }
        break;
      }
      case 'f': // face definition
      {
        currentLine.erase(0, 1);

        size_t start0 = currentLine.find_first_of(' ');
        size_t end0   = currentLine.find_first_of(' ', start0+1);
        size_t start1 = currentLine.find_first_of(' ', end0);
        size_t end1   = currentLine.find_first_of(' ', start1+1);
        size_t start2 = currentLine.find_first_of(' ', end1);
        size_t end2   = currentLine.find_first_of(' ', start2+1);

        int p1 = 0, p2 = 0, p3 = 0;

        size_t nSlashes = std::count(currentLine.begin(), currentLine.end(), '/');
        bool hasTexture = nSlashes > 0;

        if(start0 != std::string::npos && start0 < currentLine.size())
          try {
          std::string sub = currentLine.substr(start0, end0 - start0);
          if (!hasTexture)
          {
            p1 = stoi(sub);
          }
          else
          {
            //                    currentLine.count
            auto a = currentLine.find_first_of('/');
            std::string first = currentLine.substr();

          }
        } catch (...) { }

        if (start1 != std::string::npos && start1 < currentLine.size())
          try {
          std::string sub = currentLine.substr(start1, end1 - start1);
          if (!hasTexture)
          {
            p2 = stoi(sub);
          }
          else
          {
          }
        }catch (...) { }

        if (start2 != std::string::npos && start2 < currentLine.size())
          try {
          std::string sub = currentLine.substr(start2, end2 - start2);
          if (!hasTexture)
          {
            p3 = stoi(sub);
          }
          else
          {
          }
        }catch (...) { }

        //glm::vec3 triangle(
        //  vertices[p1],
        //  vertices[p2],
        //  vertices[p3]
        //);

//        _mesh.tris.push_back(triangle);
        break;
      }
      default:
        break;
      }
    }
    fin.close();

    /**/
    return true;
  }
}

int getline_NERV(char ** lineptr, size_t * n, FILE * stream)
{
	static char line[256];
	char *ptr;
	unsigned int len;

	if (lineptr == NULL || n == NULL)
	{
		errno = EINVAL;
		return -1;
	}

	if (ferror(stream))
		return -1;

	if (feof(stream))
		return -1;

	fgets(line, 256, stream);

	ptr = strchr(line, '\n');
	if (ptr)
		*ptr = '\0';

	len = strlen(line);

	if ((len + 1) < 256)
	{
		ptr = (char*)realloc(*lineptr, 256);
		if (ptr == NULL)
			return(-1);
		*lineptr = ptr;
		*n = 256;
	}

	strcpy(*lineptr, line);
	return(len);
}
