//
// Created by phil on 18.02.20.
//


#include "bepch.h"
#include "LinuxInput.h"
#include "engine/Application.h"

#include <GLFW/glfw3.h>

namespace Engine {

  Input* Input::s_Instance = new LinuxInput();

  bool LinuxInput::IsKeyPressedImpl(int keycode) {
    auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
    auto state = glfwGetKey(window, keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
  }

  bool LinuxInput::IsMouseButtonPressedImpl(int button) {
    auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
    auto state = glfwGetMouseButton(window, button);
    return state == GLFW_PRESS;
  }
  std::pair<float, float> LinuxInput::GetMousePositionImpl() {
    auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return {(float)xpos, (float)ypos};
  }
  float LinuxInput::GetMouseXImpl() {
    auto [x, y] = GetMousePositionImpl();
    return x;
  }
  float LinuxInput::GetMouseYImpl() {
    auto [x, y] = GetMousePositionImpl();
    return y;
  }



}
