//
// Created by phil on 22.02.20.
//

#include "bepch.h"
#include "OpenGLContext.h"


namespace Engine {

  OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
  :m_WindowHandle(windowHandle){
    BE_ASSERT(windowHandle, "Window handle does not exist");
  }

  void OpenGLContext::Init() {
    glfwMakeContextCurrent(m_WindowHandle);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    BE_CORE_ASSERT(status, "Failed to initialize GLAD!");

    BE_CORE_INFO("OpenGL Info:");
    BE_CORE_INFO("\tVendor: {0}", glGetString(GL_VENDOR));
    BE_CORE_INFO("\tRenderer: {0}", glGetString(GL_RENDER));
    BE_CORE_INFO("\tVersion: {0}", glGetString(GL_VERSION));
  }

  void OpenGLContext::SwapBuffers() {
    glfwSwapBuffers(m_WindowHandle);
  }
}