/**
 * File              : X11Window.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 16.02.2020
 * Last Modified Date: 17.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */

#include "bepch.h"
#include "X11Window.h"

namespace Engine {

  static bool s_GLFWInitialized = false;
  X11Window::X11Window(const WindowProps& props){
    Init(props);
  }

  X11Window::~X11Window()
  {
  }

  Window* Window::Create(const WindowProps& props){
    return new X11Window(props);
  }


  void X11Window::Init(const WindowProps& props){
    m_Data.Title = props.Title;
    m_Data.Height = props.Height;
    m_Data.Width = props.Width;

    BE_CORE_INFO("Creating window {0} ({1} {2})", props.Title, props.Width, props.Height);

    if(!s_GLFWInitialized){
      int success = glfwInit();
      BE_CORE_ASSERT(success, "Could not initialize GLFW!");

      s_GLFWInitialized = true;
    }

    m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_Window);
    glfwSetWindowUserPointer(m_Window, &m_Data);
    SetVSync(true);
  }
  void X11Window::ShutDown()
  {
    glfwDestroyWindow(m_Window);
  }

  void X11Window::OnUpdate() const {
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
  }

  void X11Window::SetVSync(bool enabled){
    if(enabled){
      glfwSwapInterval(1);
    }
    else {
      glfwSwapInterval(0);
    }

    m_Data.VSync = enabled;
  }
  bool X11Window::IsVSync() const {
    return m_Data.VSync;
  }
}
