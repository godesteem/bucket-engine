/**
 * File              : ImGUILayer.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 18.02.2020
 * Last Modified Date: 18.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include "bepch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "platform/opengl/imGUIOpenGLRenderer.h"

#include "engine/Application.h"

// TODO: Temporary

#include <glad/glad.h>


namespace Engine {

    static int reset_mouse_button = -1;

    ImGUILayer::ImGUILayer()
    : Layer("ImGUILayer")
    {
    }

    ImGUILayer::~ImGUILayer()
    {
    }

    void ImGUILayer::OnAttach()
    {
      ImGui::CreateContext();
      ImGui::StyleColorsDark();

      ImGuiIO& io = ImGui::GetIO();
      io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
      io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

      // TEMPORARY: should eventually use Hazel key codes
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
      io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
      io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
      io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
      io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
      io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
      io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

      ImGui_ImplOpenGL3_Init("#version 130");
      io.SetClipboardTextFn = SetClipboardText;
      io.GetClipboardTextFn = GetClipboardText;
      //io.ClipboardUserData = g_Window;
#if defined(_WIN32)
      //io.ImeWindowHandle = (void*)glfwGetWin32Window(g_Window);
#endif
    }

    void ImGUILayer::OnDetach()
    {

    }

    void ImGUILayer::OnUpdate()
    {
      ImGuiIO& io = ImGui::GetIO();
      BE_TRACE("Update: {0}", (void*)&io);
      BE_TRACE("ImGUILayer::OnUpdate: io.MouseDown[0] = {0}", io.MouseDown[0]);
      Application& app = Application::Get();
      io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

      auto time = (float)glfwGetTime();
      io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
      m_Time = time;

      ImGui_ImplOpenGL3_NewFrame();
      ImGui::NewFrame();

      static bool show = true;
      ImGui::ShowDemoWindow(&show);

      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      if(reset_mouse_button > -1){
        io.MouseDown[reset_mouse_button] = false;
      }
    }

    void ImGUILayer::OnEvent(Event& event)
    {
      EventDispatcher dispatcher(event);
      dispatcher.Dispatch<MouseButtonPressedEvent>(BE_BIND_EVENT_FN(ImGUILayer::OnMouseButtonPressedEvent));
      dispatcher.Dispatch<MouseButtonReleasedEvent>(BE_BIND_EVENT_FN(ImGUILayer::OnMouseButtonReleasedEvent));
      dispatcher.Dispatch<MouseMovedEvent>(BE_BIND_EVENT_FN(ImGUILayer::OnMouseMovedEvent));
      dispatcher.Dispatch<MouseScrollEvent>(BE_BIND_EVENT_FN(ImGUILayer::OnMouseScrolledEvent));
      dispatcher.Dispatch<KeyPressedEvent>(BE_BIND_EVENT_FN(ImGUILayer::OnKeyPressedEvent));
      dispatcher.Dispatch<KeyTypedEvent>(BE_BIND_EVENT_FN(ImGUILayer::OnKeyTypedEvent));
      dispatcher.Dispatch<KeyReleasedEvent>(BE_BIND_EVENT_FN(ImGUILayer::OnKeyReleasedEvent));
      dispatcher.Dispatch<WindowResizeEvent>(BE_BIND_EVENT_FN(ImGUILayer::OnWindowResizeEvent));
    }

    bool ImGUILayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
    {
      ImGuiIO& io = ImGui::GetIO();
      BE_TRACE("Event: {0}", (void*)&io);
      io.MouseDown[e.GetMouseButton()] = true;

      return false;
    }

    bool ImGUILayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
    {
      ImGuiIO& io = ImGui::GetIO();
      reset_mouse_button = e.GetMouseButton();

      return false;
    }

    bool ImGUILayer::OnMouseMovedEvent(MouseMovedEvent& e)
    {
      ImGuiIO& io = ImGui::GetIO();
      io.MousePos = ImVec2(e.GetX(), e.GetY());

      return false;
    }

    bool ImGUILayer::OnMouseScrolledEvent(MouseScrollEvent& e)
    {
      ImGuiIO& io = ImGui::GetIO();
      io.MouseWheelH += e.GetXOffset();
      io.MouseWheel += e.GetYOffset();

      return false;
    }

    bool ImGUILayer::OnKeyPressedEvent(KeyPressedEvent& e)
    {
      ImGuiIO& io = ImGui::GetIO();
      io.KeysDown[e.GetKeyCode()] = true;

      io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
      io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
      io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
      io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
      return false;
    }

    bool ImGUILayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
    {
      ImGuiIO& io = ImGui::GetIO();
      io.KeysDown[e.GetKeyCode()] = false;

      return false;
    }

    bool ImGUILayer::OnKeyTypedEvent(KeyTypedEvent& e)
    {
      ImGuiIO& io = ImGui::GetIO();
      int keycode = e.GetKeyCode();
      if (keycode > 0 && keycode < 0x10000)
        io.AddInputCharacter((unsigned short)keycode);

      return false;
    }

    bool ImGUILayer::OnWindowResizeEvent(WindowResizeEvent& e)
    {
      ImGuiIO& io = ImGui::GetIO();
      io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
      io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
      glViewport(0, 0, e.GetWidth(), e.GetHeight());

      return false;
    }

}