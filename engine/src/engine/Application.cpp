#include "bepch.h"
#include "Application.h"
#include "engine/renderer/Renderer.h"

#include "Log.h"
#include "Input.h"
#include <chrono>
namespace Engine {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

  Application* Application::s_Instance = nullptr;

  Application::Application()
  {
    BE_INFO("Creating application");
    BE_ASSERT(!s_Instance, "Application already exists.");
    s_Instance = this;

    m_Window = Scope<Window>(Window::Create(m_Settings.m_WindowProps));
    m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

    Renderer::Init();

    m_ImGuiLayer = new ImGUILayer();
    PushOverlay(m_ImGuiLayer);
  }

  Application::~Application(){

  }

  void Application::OnEvent(Event& e){
    // BE_CORE_TRACE("{0}", e);

    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
    dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

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
  bool Application::OnWindowResize(WindowResizeEvent& e){
    m_Settings.m_WindowProps.Height = e.GetHeight();
    m_Settings.m_WindowProps.Width = e.GetWidth();
    m_Window->Resize(m_Settings.m_WindowProps);
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
      Timestep time{glfwGetTime()}; // TODO: Platform!
      Timestep timestep = time - m_FrameLastTime;
      m_FrameLastTime = time;

      for(Layer* layer : m_LayerStack){
        layer->OnUpdate(timestep);
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
