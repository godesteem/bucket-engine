//
// Created by phil on 22.02.20.
//
#pragma once

namespace Engine {
  class GraphicsContext {
  public:
    virtual void Init() = 0;
    virtual void SwapBuffers() = 0;
  };
}