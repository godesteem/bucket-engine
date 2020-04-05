//
// Created by phil on 10.03.20.
//

#pragma once

#include <iostream>
#include <sstream>
#include "../tests.h"
#include "engine/core/Timestep.h"

#include <functional>

void TestTimestep()
{
  // guard against adding tests twice
  static bool alreadyRan = false;
  if(alreadyRan) return;
  alreadyRan = true;

  using namespace Engine;
  Tester::addTest([=]()
  {
    Timestep t;
    BE_TEST_ONCE(t.GetMilliseconds() == 0);
  });
  Tester::addTest([=]()
  {
    Timestep t;
    BE_TEST_ONCE(t.GetSeconds() == 0);
  });
  Tester::addTest([=]()
  {
    Timestep t(1.0f);
    BE_TEST_ONCE(t.GetSeconds() == 1.0f);
  });
  Tester::addTest([=]()
  {
    Timestep t(1.0f);
    BE_TEST_ONCE(t.GetMilliseconds() == 1000.0f);
  });
  Tester::addTest([=]()
  {
    Timestep t;
    t = t + 1;
    BE_TEST_MULTI(t.GetSeconds() == 1.0f);
    BE_TEST_MULTI(t.GetMilliseconds() == 1000.0f);
    //Warning	C4715	'<lambda_bb557d9c8f4837619b6480b6a60b4f65>::operator()': not all control paths return a value
  });
  Tester::addTest([=]()
  {
    Timestep t(1.0);
    t = t - 1;
    BE_TEST_MULTI(t.GetSeconds() == 0.0f);
    BE_TEST_MULTI(t.GetMilliseconds() == 0.0f);
    //Warning	C4715	'<lambda_812a0c0e34e59e1725d88879a760847b>::operator()': not all control paths return a value

  });

  /**
    * pz: this method is purely for demonstration of a external delta producer.
    * for real usage see `Engine::Application`s implementation of the
    * main game loop.
    */
  auto deltaProducer = [=](float &ts){float fps = 60.0f;ts = (1000.f/fps);};

  Tester::addTest([=]()
  {
    Timestep t;
    float fps = 60.0f;
    float delta;
    for(int i=0; i<10; ++i){
      deltaProducer(delta);
      t = t + delta;
    }
    float frameTime = 1000.f/fps;
    BE_TEST_MULTI(t - (10.0f * frameTime) <= 0.0001);
    //Warning	C4715	'<lambda_d46812fce8d74eb6faf7b7105a2d707d>::operator()': not all control paths return a value
  });
}
