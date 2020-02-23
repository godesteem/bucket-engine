/**
 * File              : Application.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 15.02.2020
 * Last Modified Date: 23.02.2020
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

    m_VertexArray.reset(VertexArray::Create());

    float vertices [3 * 7] = {
        -0.5f, -0.5f,  0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
         0.5f, -0.5f,  0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
         0.5f,  0.5f,  0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
    };
    m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices))); 
    BufferLayout layout = {
      { ShaderDataType::Float3, "position" },
      { ShaderDataType::Float4, "color" }
    };
    
    m_VertexBuffer->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(m_VertexBuffer);

    uint32_t indices[3] = {0, 1, 2};
    m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/ sizeof(uint32_t)));
    m_VertexArray->SetIndexBuffer(m_IndexBuffer);

    std::string vertexSrc = R"(
      #version 130
      in vec3 position;
      in vec4 color;

      out vec3 v_Position;
      out vec4 v_Color;

      void main() {
        v_Position = position + 0.5;
        v_Color = color;
        gl_Position = vec4(position + 0.5, 1.0);
      }
    )";
    std::string fragmentSrc = R"(
      #version 130
      in vec4 v_Color;
      in vec3 v_Position;
      out vec4 color;
      void main() {
        color = vec4(v_Position * 0.5 + 0.5, 1.0);
        color = v_Color;
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
      m_VertexArray->Bind();
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
