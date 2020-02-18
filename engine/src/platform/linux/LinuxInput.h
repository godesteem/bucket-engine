//
// Created by phil on 18.02.20.
//
#pragma once

#include "engine/Core.h"

#include "engine/Input.h"
namespace Engine {

  class LinuxInput: public  Input
  {
  protected:
    virtual bool IsKeyPressedImpl(int keycode) override ;
    virtual bool IsMouseButtonPressedImpl(int button) override ;
    virtual std::pair<float,float> GetMousePositionImpl() override ;
    virtual float GetMouseXImpl() override ;
    virtual float GetMouseYImpl() override ;

  };


}