/**
 * File              : Input.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 25.02.2020
 * Last Modified Date: 25.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
//
// Created by phil on 18.02.20.
//
#pragma once

#include "bepch.h"
#include "engine/core/Core.h"

namespace Engine {

  class BE_API Input
  {
  public:
    inline static bool IsKeyPressed(int keycode){ return s_Instance->IsKeyPressedImpl(keycode); };

    inline static bool IsMouseButtonPressed(int button){ return s_Instance->IsMouseButtonPressedImpl(button); };

    inline static std::pair<float,float> GetMousePosition(){ return s_Instance->GetMousePositionImpl(); };
    inline static float GetMouseX(){ return s_Instance->GetMouseXImpl(); };
    inline static float GetMouseY(){ return s_Instance->GetMouseYImpl(); };
  protected:
    virtual bool IsKeyPressedImpl(int keycode) = 0;

    virtual bool IsMouseButtonPressedImpl(int button) = 0;
    virtual std::pair<float,float> GetMousePositionImpl() = 0;
    virtual float GetMouseXImpl() = 0;
    virtual float GetMouseYImpl() = 0;
  private:
    static Input* s_Instance;
  };

}