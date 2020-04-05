#include "bepch.h"
#include "Shader.h"
#include "Renderer.h"

#include "platform/opengl/OpenGLShader.h"

namespace Engine {
  Ref<Shader> Shader::Create(const std::string& filePath){
    std::string absoluteFilePath;
    absoluteFilePath = CONSTRUCT_FILE_PATH(filePath);
    switch(Renderer::GetAPI()){
      case RendererAPI::API::None: BE_CORE_ASSERT(false, "RendererAPI::None is currently not supported ");
      case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(absoluteFilePath);
    }
    BE_CORE_ASSERT(false, "Unknown RendererAPI");
    return nullptr; 
  }

  Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc){
    switch(Renderer::GetAPI()){
      case RendererAPI::API::None: BE_CORE_ASSERT(false, "RendererAPI::None is currently not supported ");
      case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
    }
    BE_CORE_ASSERT(false, "Unknown RendererAPI");
    return nullptr; 
  }
  void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader){
    if(Exists(name)) {
      BE_CORE_WARN("Shader {0} already exists with shader {1}", name, shader->GetName());
      Remove(name);
      BE_CORE_WARN("Dropped shader {0}", name);
    }
    m_Shaders[name] = shader;
  }
  void ShaderLibrary::Add(const Ref<Shader>& shader){
    auto& name = shader->GetName();
    Add(name, shader);
  }
  Ref<Shader> ShaderLibrary::Load(const std::string& filePath){
    auto shader = Shader::Create(filePath);
    Add(shader);
    return shader;
  }
  Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filePath){
    auto shader = Shader::Create(filePath);
    Add(name, shader);
    return shader;
  }
  Ref<Shader> ShaderLibrary::Get(const std::string& name){
    BE_CORE_ASSERT(Exists(name), "Shader not found.");
    return m_Shaders[name];
  }

  bool ShaderLibrary::Exists(const std::string& name) const{
    return m_Shaders.size() > 0 && m_Shaders.find(name) != m_Shaders.end();
  }

  void ShaderLibrary::Remove(const std::string& name) {
    BE_CORE_ASSERT(Exists(name), "Shader not found.");
    m_Shaders.erase(name);
  }
}
