//
// Created by phil on 22.02.20.
//
#pragma once

#include "engine/renderer/GraphicsContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct GLFWwindow;

namespace Engine {
  class OpenGLContext: public GraphicsContext
  {
  public:
    explicit OpenGLContext(GLFWwindow* windowHandle);
    void Init() override ;
    void SwapBuffers() override ;

  private:
    GLFWwindow* m_WindowHandle;


  };
}