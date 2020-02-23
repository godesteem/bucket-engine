/**
 * File              : Application.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 15.02.2020
 * Last Modified Date: 22.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include "bepch.h"
#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "Log.h"
#include "Input.h"

namespace Engine {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
  
  Application* Application::s_Instance = nullptr;
  
  Application::Application(){
    BE_INFO("Creating application");
    BE_ASSERT(!s_Instance, "Application already exists.");
    s_Instance = this;
    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
    m_ImGuiLayer = new ImGUILayer();
    PushOverlay(m_ImGuiLayer);


    // Vertex Array
    // Vertex Buffer
    // Index Buffer
    glGenVertexArrays(1, &m_VertexArray);
    glBindVertexArray(m_VertexArray);

    //glGenBuffers(1, &m_VertexBuffer);
    //glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

    float vertices [4 * 3] = {
        -0.5f, -0.5f,  0.0f,
         0.5f, -0.5f,  0.0f,
         0.5f,  0.5f,  0.0f,
        -0.5f,  0.5f,  0.0f,
    };
    BE_CORE_TRACE("Setting VertexBuffer");
    m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
    m_VertexBuffer->Bind();
    BE_CORE_TRACE("VertexBuffer set.");
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    //glGenBuffers(1, &m_IndexBuffer);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

    BE_CORE_TRACE("Setting IndexBuffer");
    uint32_t indices[6] = {0, 1, 2, 2, 3, 0};
    m_IndexBuffer.reset(IndexBuffer::Create(indices, 6));
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

    std::string vertexSrc = R"(
      #version 130
      in vec3 position;
      out vec3 v_Position;

      void main() {
        v_Position = position + 0.5;
        gl_Position = vec4(position + 0.5, 1.0);
      }
    )";
    std::string fragmentSrc = R"(
      #version 130
      out vec4 Color;
      in vec3 v_Position;

      void main() {
        Color = vec4(v_Position * 0.5 + 0.5, 1.0);
      }
    )";

    BE_CORE_TRACE("Setting Shader");
    m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

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
      glClearColor(0.1f, 0.1f, 0.1f, 1);
      glClear(GL_COLOR_BUFFER_BIT);
      
      m_Shader->Bind();
      glBindVertexArray(m_VertexArray);
      glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

      for(Layer* layer : m_LayerStack){
        layer->OnUpdate();
      }

      m_ImGuiLayer->Begin();
      for(Layer* layer : m_LayerStack){
        layer->OnImGuiRender();
      }
      m_ImGuiLayer->End();

      m_Window->OnUpdate();
    }
  }
  inline std::ostream& operator << (std::ostream& os, const Application& app){
    return os  << "Running: " << (app.IsRunning() ? "True" : "False");
  }


}
