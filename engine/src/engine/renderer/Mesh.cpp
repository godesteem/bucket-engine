#include "Mesh.h"
#include "Renderer.h"
#include "platform/opengl/OpenGLMesh.h"
#include <fstream>

namespace Engine
{
  Ref<Mesh> Mesh::Create(const std::string &objectFilePath, const std::string &shaderFilePath) {
    switch(Renderer::GetAPI()) {
      case RendererAPI::API::None: BE_CORE_ASSERT(false, "RendererAPI::None is currently not supported ");
      case RendererAPI::API::OpenGL: return std::make_shared<OpenGLMesh>(objectFilePath, shaderFilePath);
    }
    BE_CORE_ASSERT(false, "Unknown RendererAPI");
    return nullptr;

  }

  Ref<Mesh> Mesh::Create(Ref<VertexBuffer>& vertexBuffer, Ref<IndexBuffer>& indexBuffer, const std::string& shaderFile) {
    switch(Renderer::GetAPI()) {
      case RendererAPI::API::None: BE_CORE_ASSERT(false, "RendererAPI::None is currently not supported ");
      case RendererAPI::API::OpenGL: return std::make_shared<OpenGLMesh>(vertexBuffer, indexBuffer, shaderFile);
    }
    BE_CORE_ASSERT(false, "Unknown RendererAPI");
    return nullptr;
  }

  ObjFile::ObjFile(const std::string& fp)
    : _filePath(CONSTRUCT_FILE_PATH(fp))
  {
    LoadObjFile(this->_filePath);
  }

  ObjFile::~ObjFile()
  {
    saveObjFile(); // for testing
  }

  void ObjFile::CreateObjFile(float* vertices, size_t vertexCount, VertexCategory vertexCategories, size_t vertexElementCount, uint32_t* indices, size_t indexCount, const std::string& fp) {
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> _vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> _normals;

    std::string resultFilePath = CONSTRUCT_FILE_PATH(fp);
    FILE* resultFile = fopen(resultFilePath.c_str(), "w");
    if (resultFile == nullptr) {
      BE_CORE_ASSERT(false, "File " + fp + " can not be opened.");
    }
    std::ostringstream vertexStream, uvStream, normalStream, faceStream;
    for (size_t index = 0; index<vertexCount; ++index) {
      size_t realIndex = index * vertexElementCount;
      if (static_cast<bool>(vertexCategories & VertexCategory::Vertex)) {
        vertexStream << "v "
                     << vertices[realIndex]
                     << ' '
                     << vertices[realIndex + 1]
                     << ' '
                     << vertices[realIndex + 2]
                     << '\n';
      }
      if (static_cast<bool>(vertexCategories & VertexCategory::UV)) {
        uvStream << "vt "
                 << vertices[realIndex + 3]
                 << ' '
                 << vertices[realIndex + 4]
                 << '\n';
      }
      if (static_cast<bool>(vertexCategories & VertexCategory::Normal)) {
        normalStream << "vn "
                     << vertices[realIndex + 5]
                     << ' '
                     << vertices[realIndex + 6]
                     << '\n';
      }
    }
    for (size_t index = 0; index<indexCount; ++index) {
      if (index % 3 == 0) {
        faceStream << "f ";
      }
      faceStream << index;
      if (index % 3 == 2) {
        faceStream << "\n";
      }
      else {
        faceStream << " ";
      }
    }
    if(resultFile == nullptr) { resultFile = fopen(resultFilePath.c_str(), "w"); };
    for(auto elem : "# auto generated file\n") putc(elem, resultFile);
    for(auto elem : "# " + fp + "\n") putc(elem, resultFile);
    for(auto elem : vertexStream.str()) putc(elem, resultFile);
    for(auto elem : normalStream.str()) putc(elem, resultFile);
    for(auto elem : faceStream.str()) putc(elem, resultFile);
    fclose(resultFile);
    resultFile = nullptr;
  }

  bool ObjFile::LoadObjFile(std::string const& fileName)
  {
    std::ifstream fin(fileName);
    if (!fin)
    {
      BE_CORE_ASSERT(false, std::string() + __FUNCTION__ + " File " + fileName + " can not be opened.");
      fin.close();
      return false;
    }

    // clear potentially existing data
    _vertices.clear();
    _normals.clear();
    _texture_uvs.clear();

    // stupid 1-indexed data, pushback one so everything is nice...
    _vertices.push_back(Engine::Math::vec3());
    _normals.push_back(Engine::Math::vec3());
    _texture_uvs.push_back(Engine::Math::vec2());

    while(!fin.eof())
    {
      const size_t bufSize = 1024;
      char buf[bufSize];

      fin.get(buf, bufSize, '\n');
      fin.ignore(); // remove the '\n' from the file
      if(buf[0] == '\0')
      {
        fin.ignore('\0');
        continue;
      }
      switch (buf[0])
      {
      case '#':
        // comment, ignore line
        break;

      case 'v':
        // line may contain a vertex
      {
        const char vertexKind = buf[1];
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

        std::string currentLine(buf +1);

        // sigh: https://stackoverflow.com/questions/8362094/replace-multiple-spaces-with-one-space-in-a-string
        // temporary fix to remove unnecessary multiple whitespace
        std::string::iterator new_end = std::unique(currentLine.begin(), currentLine.end(), [=](char lhs, char rhs){ return (lhs == rhs) && (lhs == ' '); } );
        currentLine.erase(new_end, currentLine.end());

        // because the following only expects a single space per separation...
        size_t start0 = currentLine.find_first_of(' ');
        size_t end0   = currentLine.find_first_of(' ', start0+1);
        size_t start1 = currentLine.find_first_of(' ', end0);
        size_t end1   = currentLine.find_first_of(' ', start1+1);
        size_t start2 = currentLine.find_first_of(' ', end1);
        size_t end2   = currentLine.find_first_of(' ', start2+1);

        switch (vertexKind)
        {
        case ' ':
        case 'n': // geometric vertex
        {
          float x = 0, y = 0, z = 0;

          // jnl: read https://stackoverflow.com/a/57865805/10314791 atof is way faster, accepting the caveats
          if(start0 != std::string::npos && start0 < currentLine.size())
          try {
            x = atof(currentLine.c_str() + start0);
          } catch (...) { }

          if (start1 != std::string::npos && start1 < currentLine.size())
          try {
            y = atof(currentLine.c_str() + start1);
          }catch (...) { }

          if (start2 != std::string::npos && start2 < currentLine.size())
          try {
            z = atof(currentLine.c_str() + start2);
          }catch (...) { }

          Engine::Math::vec3 v{{x},{y},{z}};
          if(vertexKind == 'n') { _normals.push_back(v); }
          else { _vertices.push_back(v); }
          break;
        }
        case 't':
        // texture vertex
        {
          float x = 0, y = 0;

          if(start0 != std::string::npos && start0 < currentLine.size())
          try {
            x = atof(currentLine.c_str() + start0);
          } catch (...) { }

          if (start1 != std::string::npos && start1 < currentLine.size())
          try {
            y = atof(currentLine.c_str() + start1);
          }catch (...) { }

          Engine::Math::vec2 v{{x}, {y}};
          _texture_uvs.push_back(v);
          break;
        }
        default: // dont handle anything else
          break;
        }
        break;
      }
      case 'f': // face definition
      {
        std::string currentLine(buf+1);

        // sigh: https://stackoverflow.com/questions/8362094/replace-multiple-spaces-with-one-space-in-a-string
        // temporary fix to remove unnecessary multiple whitespace
        std::string::iterator new_end = std::unique(currentLine.begin(), currentLine.end(), [=](char lhs, char rhs){ return (lhs == rhs) && (lhs == ' '); } );
        currentLine.erase(new_end, currentLine.end());

        size_t nSlashes = std::count(currentLine.begin(), currentLine.end(), '/');
        size_t nDoubleSlashes = 0;
        for (size_t i = 0; i < currentLine.size()-1; ++i)
        {
          nDoubleSlashes += currentLine[i] == currentLine[i+1] && currentLine[i] == '/';
        }

        _hasTextures = nDoubleSlashes == 0 && nSlashes > 0;
        _hasNormals = nSlashes > 0;

        size_t start0 = currentLine.find_first_of(' ');
        size_t end0   = currentLine.find_first_of(' ', start0+1);
        size_t start1 = currentLine.find_first_of(' ', end0);
        size_t end1   = currentLine.find_first_of(' ', start1+1);
        size_t start2 = currentLine.find_first_of(' ', end1);
        size_t end2   = currentLine.size();

        face newFace;

        if(start0 != std::string::npos && start0 < currentLine.size())
          try {
            std::string sub = currentLine.substr(start0, end0 - start0);
          if (!_hasNormals) {
            newFace.p1.vertex = stoi(sub);
          }
          else
          {
            size_t endVal = sub.find_first_of('/');
            std::string val = sub.substr(0, endVal);
            newFace.p1.vertex = stoi(val);
            size_t endVal2 = sub.find_first_of('/', endVal + 1);
            if(_hasTextures) {
              val = sub.substr(endVal + 1, endVal2);
              newFace.p1.texture = stoi(val);
            }
            int endVal3 = sub.find_first_of('/', endVal2 + 1);
            val = sub.substr(endVal2 + 1, endVal3);
            newFace.p1.normal = stoi(val);
          }
        } catch (...) { }

        if (start1 != std::string::npos && start1 < currentLine.size())
          try {
          std::string sub = currentLine.substr(start1, end1 - start1);
          if (!_hasNormals) {
            newFace.p2.vertex = stoi(sub);
          }
          else
          {
            size_t endVal = sub.find_first_of('/');
            std::string val = sub.substr(0, endVal);
            newFace.p2.vertex = stoi(val);
            size_t endVal2 = sub.find_first_of('/', endVal + 1);
            if(_hasTextures) {
              val = sub.substr(endVal + 1, endVal2);
              newFace.p2.texture = stoi(val);
            }
            size_t endVal3 = sub.find_first_of('/', endVal2 + 1);
            val = sub.substr(endVal2 + 1, endVal3);
            newFace.p2.normal = stoi(val);
          }
        }catch (...) { }

        if (start2 != std::string::npos && start2 < currentLine.size())
        try {
          std::string sub = currentLine.substr(start2, end2 - start2);
          if (!_hasNormals) {
            newFace.p3.vertex = stoi(sub);
          }
          else {
            size_t endVal = sub.find_first_of('/');
            std::string val = sub.substr(0, endVal);
            newFace.p3.vertex = stoi(val);
            size_t endVal2 = sub.find_first_of('/', endVal + 1);
            if(_hasTextures) {
              val = sub.substr(endVal + 1, endVal2);
              newFace.p3.texture = stoi(val);
            }
            size_t endVal3 = sub.find_first_of('/', endVal2 + 1);
            val = sub.substr(endVal2 + 1, endVal3);
            newFace.p3.normal = stoi(val);
          }
        }catch (...) { }

        _faces.push_back(newFace);
        break;
      }
      default:
        break;
      }
    }
    fin.close();
    return true;
  }
  bool ObjFile::saveObjFile(std::string const& fileName)
  {
    std::ofstream fout(fileName + "_out.obj");
    if(!fout)
    {
      fout.close();
      return false;
    }
    fout << "# auto generated file\n";
    fout << "# " + fileName + "\n";
    bool ignoreFirst = true;

    ignoreFirst = true;
    for (auto& v : this->_vertices) { if(ignoreFirst) {ignoreFirst = false; continue;} fout << "v  " << v.x() << ' ' << v.y() << ' ' << v.z() << '\n'; }
    fout << '\n';

    ignoreFirst = true;
    for (auto& vt : this->_texture_uvs) { if(ignoreFirst) {ignoreFirst = false; continue;} fout << "vt " << vt.x() << ' ' << vt.y() << '\n'; }
    fout << '\n';

    ignoreFirst = true;
    for (auto& vn : this->_normals) { if(ignoreFirst) {ignoreFirst = false; continue;} fout << "vn " << vn.x() << ' ' << vn.y() << ' ' << vn.z() << '\n'; }
    fout << '\n';

    ignoreFirst = false;
    for (auto& f : this->_faces) { if(ignoreFirst) {ignoreFirst = false; continue;} fout << "f " << f.p1 << ' ' << f.p2 << ' ' << f.p3 << '\n'; }
    fout << '\n';

    fout.close();
    return true;
  }
} // namespace Engine
