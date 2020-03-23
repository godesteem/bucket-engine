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
    LoadObjFile(this->filePath);
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

  bool ObjFile::LoadObjFile(std::string const& fileName)
  {
  /* */
    std::ifstream fin(fileName);

    if (!fin)
    {
      BE_CORE_ASSERT(false, std::string() + __FUNCTION__ + " File " + fileName + " can not be opened.");
      fin.close();
      return false;
    }
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;

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
        case 'n':
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
          if(vertexKind == 'n'){
            temp_normals.push_back(v);
          } else {
            temp_vertices.push_back(v);
          }
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
          temp_uvs.push_back(v);
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

        size_t nSlashes = std::count(currentLine.begin(), currentLine.end(), '/');
        size_t nDoubleSlashes = std::count(currentLine.begin(), currentLine.end(), '//');

        hasUVs = nDoubleSlashes == 0 && nSlashes > 0;
        hasNormals = nSlashes > 0;

        size_t start0 = currentLine.find_first_of(' ');
        size_t end0 = currentLine.find_first_of(' ', start0+1);
        size_t start1 = currentLine.find_first_of(' ', end0);
        size_t end1   = currentLine.find_first_of(' ', start1+1);
        size_t start2 = currentLine.find_first_of(' ', end1);
        size_t end2   = currentLine.size();

        int  v1 = 0,  v2 = 0,  v3 = 0, \
            vn1 = 0, vn2 = 0, vn3 = 0, \
            vt1 = 0, vt2 = 0, vt3 = 0;

        if(start0 != std::string::npos && start0 < currentLine.size())
          try {
            std::string sub = currentLine.substr(start0, end0 - start0);
          if (!hasNormals)
          {
            v1 = stoi(sub);
          }
          else
          {
            int endVal = sub.find_first_of('/');
            std::string val = sub.substr(0, endVal);
            v1 = stoi(val);
            int endVal2 = sub.find_first_of('/', endVal);
            if(hasUVs){
              val = sub.substr(endVal + 1, endVal2);
              vt1 = stoi(val);
            }
            int endVal3 = sub.find_first_of('/', endVal2);
            val = sub.substr(endVal2 + 1, endVal3);
            vn1 = stoi(val);
          }
        } catch (...) { }

        if (start1 != std::string::npos && start1 < currentLine.size())
          try {
          std::string sub = currentLine.substr(start1, end1 - start1);
          if (!hasNormals)
          {
            v2 = stoi(sub);
          }
          else
          {
            int endVal = sub.find_first_of('/');
            std::string val = sub.substr(0, endVal);
            v2 = stoi(val);
            int endVal2 = sub.find_first_of('/', endVal);
            if(hasUVs){
              val = sub.substr(endVal + 1, endVal2);
              vt2 = stoi(val);
            }
            int endVal3 = sub.find_first_of('/', endVal2);
            val = sub.substr(endVal2 + 1, endVal3);
            vn2 = stoi(val);
          }
        }catch (...) { }

        if (start2 != std::string::npos && start2 < currentLine.size())
          try {
          std::string sub = currentLine.substr(start2, end2 - start2);
          if (!hasNormals)
          {
            v3 = stoi(sub);
          }
          else
          {
            int endVal = sub.find_first_of('/');
            std::string val = sub.substr(0, endVal);
            v3 = stoi(val);
            int endVal2 = sub.find_first_of('/', endVal);
            if(hasUVs){
              val = sub.substr(endVal + 1, endVal2);
              vt3 = stoi(val);
            }
            int endVal3 = sub.find_first_of('/', endVal2);
            val = sub.substr(endVal2 + 1, endVal3);
            vn3 = stoi(val);
          }
        }catch (...) { }

        vertexIndices.push_back(v1);
        vertexIndices.push_back(v2);
        vertexIndices.push_back(v3);
        if (hasUVs) {
          uvIndices.push_back(vt1);
          uvIndices.push_back(vt2);
          uvIndices.push_back(vt3);
        }
        if (hasNormals) {
          normalIndices.push_back(vn1);
          normalIndices.push_back(vn2);
          normalIndices.push_back(vn3);
        }

        break;
      }
      default:
        break;
      }
    }
    fin.close();

    int correction = 1;
    for (auto index : vertexIndices) {
      if (index == 0)
      {
        correction = 0;
        break;
      }
    }

    // For each vertex of each triangle
    for (unsigned int i = 0; i < vertexIndices.size(); i++)
    {
      if (!temp_vertices.empty() && !vertexIndices.empty()) {
        unsigned int vertexIndex = vertexIndices[i];
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
        glm::vec3 normal = temp_normals.at(normalIndex - correction); // jnl: lief bei mir out of range, habs zu at() geaendert, damit es dann bei dir meckert
        this->normals.push_back(normal);
      }
    }
    /**/
    return true;
  }
}

#ifdef BE_PLATFORM_WINDOWS
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
#endif
