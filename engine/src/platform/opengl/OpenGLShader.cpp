/**
 * File              : OpenGLShader.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 25.02.2020
 * Last Modified Date: 29.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include "bepch.h"
#include "OpenGLShader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>


namespace Engine {

  static GLenum ShaderTypeFromString(const std::string& type){

    if(type == "vertex")
      return GL_VERTEX_SHADER;
    if(type == "fragment")
      return GL_FRAGMENT_SHADER;
    if(type != "pixel")
      return GL_FRAGMENT_SHADER;

    BE_CORE_TRACE("Shader type: {}", type);
    BE_CORE_ASSERT(false, "Unknown shader type!");
    return 0;
  }
  OpenGLShader::OpenGLShader(const std::string& filePath) {
    std::string shaderSrc = ReadFile(filePath);
    auto shaderSources = PreProcess(shaderSrc);
    Compile(shaderSources);
  }

  std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source){
    std::unordered_map<GLenum, std::string> shaderSources;

    const char* typeToken = "#type";
    size_t typeTokenLength = strlen(typeToken);
    size_t pos = source.find(typeToken, 0);
    while(pos != std::string::npos){
      size_t eol = 0;
      eol = source.find_first_of(NEW_LINE_CHAR, pos);
      BE_CORE_ASSERT(eol != std::string::npos, "Syntax error!");
      size_t begin = pos + typeTokenLength + 1;
      std::string type = source.substr(begin, eol - begin);
      BE_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type!");

      size_t nextLinePos = source.find_first_not_of(NEW_LINE_CHAR, eol);
      pos = source.find(typeToken, nextLinePos);
      shaderSources[ShaderTypeFromString(type)] = source.substr(
        nextLinePos, 
        pos - (nextLinePos == std::string::npos ? source.size() : nextLinePos)
      );
    }
    return shaderSources;

  }

  std::string OpenGLShader::ReadFile(const std::string& filePath){
    std::string result;
    std::ifstream in(filePath, std::ios::binary);
    if (in){
      in.seekg(0, std::ios::end);
      result.resize(in.tellg());
      in.seekg(0, std::ios::beg);
      in.read(&result[0], result.size());
      in.close();
    }
    else {
      BE_CORE_ERROR("Could not open file, {0}!", filePath);
    }
    return result; 
  }
  OpenGLShader::OpenGLShader(const std::string &vertexSrc, const std::string &fragmentSrc) {
    std::unordered_map<GLenum, std::string> sources;
    sources[GL_VERTEX_SHADER] = vertexSrc;
    sources[GL_FRAGMENT_SHADER] = fragmentSrc;

    Compile(sources);
  }

  void OpenGLShader::Compile(std::unordered_map<GLenum, std::string>& shaderSources){

    std::vector<GLenum> glShaderIDs(shaderSources.size()); 

    // Vertex and fragment shaders are successfully compiled.
    // Now time to link them together into a program.
    // Get a program object.
    GLuint program = glCreateProgram();
    for(auto& kv : shaderSources){
      GLenum type = kv.first;
      const std::string& src = kv.second;
      GLuint shader = glCreateShader(type);
      const GLchar *source = src.c_str();
      glShaderSource(shader, 1, &source, 0);
      glCompileShader(shader);
      GLint isCompiled = 0;
      glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
      if(isCompiled == GL_FALSE)
      {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

        // We don't need the shader anymore.
        glDeleteShader(shader);

        // Use the infoLog as you see fit.

        BE_CORE_ERROR("{0}", infoLog.data());
        BE_CORE_ASSERT(0, "Shader compilation failed.");
      }
      glAttachShader(program, shader);
      glShaderIDs.push_back(shader);
    }


    // Link our program
    glLinkProgram(program);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
      GLint maxLength = 0;
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

      // The maxLength includes the NULL character
      std::vector<GLchar> infoLog(maxLength);
      glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

      // We don't need the program anymore.
      glDeleteProgram(program);
      // Don't leak shaders either.
      for(auto id : glShaderIDs){
        glDeleteShader(id);
      }

      // Use the infoLog as you see fit.
      BE_CORE_ERROR("{0}", infoLog.data());
      BE_CORE_ASSERT(0, "Shader link failure.");
    }

    // Always detach shaders after a successful link.
    for(auto id : glShaderIDs){
      glDetachShader(program, id);
    }
    m_RendererID = program;
  }

  OpenGLShader::~OpenGLShader() {
    glDeleteProgram(m_RendererID);
  }

  void OpenGLShader::Bind() const {
    glUseProgram(m_RendererID);
  }

  void OpenGLShader::Unbind() const {
    glUseProgram(0);
  }

  void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix){
    GLint location = GetUniformLocation(name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
  }
  void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix){
    GLint location = GetUniformLocation(name.c_str());
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));

  }
    
  void OpenGLShader::UploadUniformFloat(const std::string& name, float value){
    GLint location = GetUniformLocation(name.c_str());
    glUniform1f(location, value);

  }
  void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& values){
    GLint location = GetUniformLocation(name.c_str());
    glUniform2f(location, values.x, values.y);

  }
  void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& values){
    GLint location = GetUniformLocation(name.c_str());
    glUniform3f(location, values.x, values.y, values.z);
  }
  void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values){
    GLint location = GetUniformLocation(name.c_str());
    glUniform4f(location, values.x, values.y, values.z, values.w);
  }
  void OpenGLShader::UploadUniformInt(const std::string& name, int value){
    GLint location = GetUniformLocation(name.c_str());
    glUniform1i(location, value);

  }
  GLint OpenGLShader::GetUniformLocation(const std::string& name) const{
    if(m_UniformLocationCache.find(name) != m_UniformLocationCache.end()){
      return m_UniformLocationCache[name];
    }
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    if(location == -1){
      BE_CORE_WARN("Uniform {0} not found", name);
      return location;
    }
    m_UniformLocationCache[name] = location;
    return location;
  }
}
