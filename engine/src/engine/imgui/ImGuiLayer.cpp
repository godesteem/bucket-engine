/**
 * File              : ImGuiLayer.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 18.02.2020
 * Last Modified Date: 23.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include "bepch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

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
      // Setup Dear ImGui context
      IMGUI_CHECKVERSION();
      ImGui::CreateContext();
      ImGuiIO& io = ImGui::GetIO(); (void)io;
      io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
      //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
      io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
      io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
      //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
      //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

      // Setup Dear ImGui style
      ImGui::StyleColorsDark();
      //ImGui::StyleColorsClassic();

      // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
      ImGuiStyle& style = ImGui::GetStyle();
      if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
      {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
      }

      Application& app = Application::Get();
      GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

      // Setup Platform/Renderer bindings
      ImGui_ImplGlfw_InitForOpenGL(window, true);
#ifdef BE_PLATFORM_LINUX
      ImGui_ImplOpenGL3_Init("#version 130");
#endif
#ifdef BE_PLATFORM_WINDOWS
      // TODO: figure out windows version.
      ImGui_ImplOpenGL3_Init("#version 130");
#endif

    }

    void ImGUILayer::OnDetach()
    {
      ImGui_ImplOpenGL3_Shutdown();
      ImGui_ImplGlfw_Shutdown();
      ImGui::DestroyContext();
    }

    void ImGUILayer::Begin() {
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();
    }

    void ImGUILayer::End() {
      ImGuiIO& io = ImGui::GetIO();
      Application& app = Application::Get();
      io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(),(float) app.GetWindow().GetHeight());

      // Rendering
      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
      {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
      }
    }

    void ImGUILayer::OnImGuiRender() {
#ifdef BE_DEBUG
      static bool show = true;
      ImGui::ShowDemoWindow(&show);
#endif
    }
}
