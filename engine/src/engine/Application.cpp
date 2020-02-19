/**
 * File              : Application.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 15.02.2020
 * Last Modified Date: 18.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include "bepch.h"
#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "Log.h"
#include "Input.h"
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
glm::mat4 camera(float Translate, glm::vec2 const & Rotate)
{
  glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
  glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
  View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
  View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
  glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
  return Projection * View * Model;
}

namespace Engine {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
  
  Application* Application::s_Instance = nullptr;
  
  Application::Application(){
    BE_INFO("Creating application");
    BE_ASSERT(!s_Instance, "Application already exists.");
    s_Instance = this;
    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
  }

  Application::~Application(){

  }

  void Application::OnEvent(Event& e){
    // BE_CORE_TRACE("{0}", e);

    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

    for(auto it=m_LayerStack.end(); it != m_LayerStack.begin();){
      (*--it)->OnEvent(e);
      if(e.Handled){
        break;
      }
    }
  }

  bool Application::OnWindowClose(WindowCloseEvent& e){
    m_Running = false;
    return true;
  }

  void Application::PushLayer(Layer* layer){
    m_LayerStack.PushLayer(layer);
    layer->OnAttach();
  }
  void Application::PushOverlay(Layer* overlay){
    m_LayerStack.PushOverlay(overlay);
    overlay->OnAttach();
  }

  void Application::Run(){
    while(m_Running){
      glClearColor(0, 0, 0, 1);
      glClear(GL_COLOR_BUFFER_BIT);
      for(Layer* layer : m_LayerStack){
        layer->OnUpdate();
      }
      m_Window->OnUpdate();
    }
  }
  inline std::ostream& operator << (std::ostream& os, const Application& app){
    return os  << "Running: " << (app.IsRunning() ? "True" : "False");
  }


}
