/**
 * File              : X11Window.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 16.02.2020
 * Last Modified Date: 22.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */

#include "bepch.h"
#include "platform/opengl/OpenGLContext.h"
#include "X11Window.h"

#include "engine/events/ApplicationEvent.h"
#include "engine/events/KeyEvent.h"
#include "engine/events/MouseEvent.h"



namespace Engine {

  static bool s_GLFWInitialized = false;

  static void GLFWErrorCallback(int err, const char* description){
    BE_CORE_ERROR("GLFW Error: ({0}) {1}", err, description);
  };
  
  Window* Window::Create(const WindowProps& props){
    return new X11Window(props);
  }

  X11Window::X11Window(const WindowProps& props){
    Init(props);
  }

  X11Window::~X11Window()
  {
  }


  void X11Window::Init(const WindowProps& props){
    m_Data.Title = props.Title;
    m_Data.Height = props.Height;
    m_Data.Width = props.Width;

    BE_CORE_INFO("Creating window {0} ({1}x{2})", props.Title, props.Width, props.Height);


    if(!s_GLFWInitialized){
      int success = glfwInit();
      BE_CORE_ASSERT(success, "Could not initialize GLFW!");
      glfwSetErrorCallback(GLFWErrorCallback);
      s_GLFWInitialized = true;
    }

    m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
    m_Context = new OpenGLContext(m_Window);
    m_Context->Init();
    glfwSetWindowUserPointer(m_Window, &m_Data);
    SetVSync(true);

    BE_CORE_INFO("Setting callbacks");

    // GLFW Callbacks
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height){
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

      data.Width = width;
      data.Height = height;

      WindowResizeEvent event(width, height);
      data.EventCallback(event);
    });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window){
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
      WindowCloseEvent event;
      data.EventCallback(event);
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods){
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
      switch(action){
        case GLFW_PRESS:{
          KeyPressedEvent event(key, 0);
          data.EventCallback(event);
          break;
        }
        case GLFW_RELEASE:{
          KeyReleasedEvent event(key);
          data.EventCallback(event);
          break;
        }
        case GLFW_REPEAT:{
          KeyPressedEvent event(key, 1);
          data.EventCallback(event);
          break;
        }
      }
    });
    glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode){
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        KeyTypedEvent event(keycode);
        data.EventCallback(event);
    });
    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods){
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
      switch(action){
        case GLFW_PRESS:{
          MouseButtonPressedEvent event(button);
          data.EventCallback(event);
          break;
        }
        case GLFW_RELEASE:{
          MouseButtonReleasedEvent event(button);
          data.EventCallback(event);
          break;
        }
      }        
    });
    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double XOffset, double YOffset){
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
      MouseScrollEvent event((float)XOffset, (float)YOffset);
     data.EventCallback(event); 
    });
    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos){
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); 
      MouseMovedEvent event(xPos, yPos);
      data.EventCallback(event);
    });

    BE_CORE_INFO("Callbacks set.");
  }
  void X11Window::ShutDown()
  {
    glfwDestroyWindow(m_Window);
  }

  void X11Window::OnUpdate() const {
    glfwPollEvents();
    m_Context->SwapBuffers();
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
