/**
 * File              : ImGuiLayer.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 18.02.2020
 * Last Modified Date: 18.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include "bepch.h"
#include "ImGuiLayer.h"
#include "imgui.h"
#include "platform/opengl/imGUIOpenGLRenderer.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "engine/Application.h"

namespace Engine {
  ImGUILayer::ImGUILayer()
  : Layer("ImGUILayer")
  {
  }

  ImGUILayer::~ImGUILayer(){

  }
  void ImGUILayer::OnAttach(){
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();

    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    // TODO: Change this!!
    // Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.
    io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
    io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
    io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
    io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
    io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
    io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
    io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
    io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
    io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
    io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
    io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
    io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
    io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
    io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
    io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
    io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
    io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
    io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
    io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
    io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

    ImGui_ImplOpenGL3_Init("#version 130");
    BE_TRACE("ImGUI attached.");
  }
  void ImGUILayer::OnDetach(){

  }

  void ImGUILayer::OnUpdate(){
    ImGuiIO& io = ImGui::GetIO();
    Application& app = Application::Get();
    io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
    
    float time = (float)glfwGetTime();
    io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60.0f);
    m_Time = time;
    
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
    

    static bool show = true;

    ImGui::ShowDemoWindow(&show);
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

  void ImGUILayer::OnEvent(Event& e){
    BE_TRACE("ImGUILayer::OnEvent: {0}", e);
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<MouseButtonPressedEvent>(BE_BIND_EVENT_FN(ImGUILayer::OnMouseButtonPressedEvent));
    dispatcher.Dispatch<MouseButtonReleasedEvent>(BE_BIND_EVENT_FN(ImGUILayer::OnMouseButtonReleasedEvent));
    dispatcher.Dispatch<MouseMovedEvent>(BE_BIND_EVENT_FN(ImGUILayer::OnMouseMovedEvent));
    dispatcher.Dispatch<MouseScrollEvent>(BE_BIND_EVENT_FN(ImGUILayer::OnMouseScrolledEvent));
    dispatcher.Dispatch<KeyPressedEvent>(BE_BIND_EVENT_FN(ImGUILayer::OnKeyPressedEvent));
    dispatcher.Dispatch<KeyReleasedEvent>(BE_BIND_EVENT_FN(ImGUILayer::OnKeyReleasedEvent));
    //dispatcher.Dispatch<KeyTypedEvent>(BE_BIND_EVENT_FN(ImGUILayer::OnKeyTypedEvent));
    dispatcher.Dispatch<WindowResizeEvent>(BE_BIND_EVENT_FN(ImGUILayer::OnWindowResizeEvent));
  }
  bool ImGUILayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e){
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[e.GetMouseButton()] = true;
    return false;
  }
  bool ImGUILayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e){
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[e.GetMouseButton()] = false;
    return false;
  
  }
  bool ImGUILayer::OnMouseMovedEvent(MouseMovedEvent& e){
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2(e.GetX(), e.GetY());
    return false;
  
  }
  bool ImGUILayer::OnMouseScrolledEvent(MouseScrollEvent& e){
    ImGuiIO& io = ImGui::GetIO();
    io.MouseWheelH += e.GetYOffset();
    io.MouseWheel += e.GetXOffset();
    return false; 
  }
  bool ImGUILayer::OnKeyPressedEvent(KeyPressedEvent& e){
    return false;
  }
  bool ImGUILayer::OnKeyReleasedEvent(KeyReleasedEvent& e){
    return false;
  }
  //bool ImGUILayer::OnKeyTypedEvent(KeyTypedEvent& e);
  bool ImGUILayer::OnWindowResizeEvent(WindowResizeEvent& e){
    return false;
  }
  
}
