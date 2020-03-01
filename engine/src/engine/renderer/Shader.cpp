/**
 * File              : Shader.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 23.02.2020
 * Last Modified Date: 01.03.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */

#include "bepch.h"
#include "Shader.h"
#include "Renderer.h"

#include "platform/opengl/OpenGLShader.h"

namespace Engine {
  Ref<Shader> Shader::Create(const std::string& filePath){
    switch(Renderer::GetAPI()){
      case RendererAPI::API::None: BE_CORE_ASSERT(false, "RendererAPI::None is currently not supported ");
      case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(filePath);
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
    BE_CORE_ASSERT(!Exists(name), "Shader already exists");
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

}
