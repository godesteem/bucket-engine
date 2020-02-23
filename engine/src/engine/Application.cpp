/**
 * File              : Application.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 15.02.2020
 * Last Modified Date: 23.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include "bepch.h"
#include "Application.h"
#include "engine/renderer/Renderer.h"


#include "Log.h"
#include "Input.h"

namespace Engine {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
  
  Application* Application::s_Instance = nullptr;
   
  Application::Application()
  : m_Camera(-3.2f, 3.2f, -1.8f, 1.8f)
  {
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
    std::shared_ptr<VertexBuffer> triangleVB;
    triangleVB.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

    BufferLayout layout = {
      { ShaderDataType::Float3, "position" },
      { ShaderDataType::Float4, "color" }
    };
    
    triangleVB->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(triangleVB);

    uint32_t indices[3] = {0, 1, 2};

    std::shared_ptr<IndexBuffer> triangleIA;
    triangleIA.reset(IndexBuffer::Create(indices, sizeof(indices)/ sizeof(uint32_t)));
    m_VertexArray->SetIndexBuffer(triangleIA);

    m_SquareVA.reset(VertexArray::Create());
    
    float squareVertices [3 * 4] = {
        -0.75f, -0.75f,  0.0f,
         0.75f, -0.75f,  0.0f,
         0.75f,  0.75f,  0.0f,
        -0.75f,  0.75f,  0.0f,
    };

    std::shared_ptr<VertexBuffer> squareVB;
    squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

    squareVB->SetLayout({
      { ShaderDataType::Float3, "position" }
    });
    m_SquareVA->AddVertexBuffer(squareVB);


    uint32_t squareIndices[6] = {
      0, 1, 2,
      2, 3, 0
    };
    std::shared_ptr<IndexBuffer> squareIA;
    squareIA.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices)/ sizeof(uint32_t)));
    m_SquareVA->SetIndexBuffer(squareIA);

    BE_CORE_TRACE("Setting Shader");
    std::string vertexSrcBlue = R"(
      #version 130
      in vec3 position;

      uniform mat4 u_ViewProjection;
      out vec3 v_Position;

      void main() {
        v_Position = position;
        gl_Position = u_ViewProjection * vec4(position, 1.0);
      }
    )";
    std::string fragmentSrcBlue = R"(
      #version 130
      in vec3 v_Position;
      out vec4 color;
      void main() {
        color = vec4(v_Position * 0.5 + 0.5, 1.0);
      }
    )";
    m_BlueShader.reset(new Shader(vertexSrcBlue, fragmentSrcBlue));

    std::string vertexSrc = R"(
      #version 130
      in vec3 position;
      in vec4 color;
      uniform mat4 u_ViewProjection;

      out vec3 v_Position;
      out vec4 v_Color;

      void main() {
        v_Position = position;
        v_Color = color;
        gl_Position = u_ViewProjection * vec4(position, 1.0);
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
      RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1});
      RenderCommand::Clear();
      
      Renderer::BeginScene(m_Camera);

      Renderer::Submit(m_SquareVA, m_BlueShader);

      Renderer::Submit(m_VertexArray, m_Shader);

      Renderer::EndScene();

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
