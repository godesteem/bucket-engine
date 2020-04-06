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
    Timestep t{0.f};
    BE_TEST_ONCE(std::chrono::duration_cast<std::chrono::milliseconds>(t) == Timestep{0.f});
  });
  Tester::addTest([=]()
  {
    Timestep t{0.f};
    BE_TEST_ONCE(t.count() == 0);
  });
  Tester::addTest([=]()
  {
    Timestep t(1.0f);
    BE_TEST_ONCE(t.count() == 1.0f);
  });
  Tester::addTest([=]()
  {
    Timestep t(1.0f);
    BE_TEST_ONCE(std::chrono::duration_cast<std::chrono::milliseconds>(t).count() == 1000.f);
  });
  Tester::addTest([=]()
  {
    Timestep t{0.f};
    t++;
    BE_TEST_MULTI(t.count() == 1.0f);
    BE_TEST_MULTI(std::chrono::duration_cast<std::chrono::milliseconds>(t).count() == 1000.f);
    return test_status::TEST_OK;
  });
  Tester::addTest([=]()
  {
    Timestep t{1.f};
    t--;
    BE_TEST_MULTI(t.count() == 0.0f);
    BE_TEST_MULTI(std::chrono::duration_cast<std::chrono::milliseconds>(t) == Timestep{0.f});
    return test_status::TEST_OK;
  });

  /**
    * pz: this method is purely for demonstration of a external delta producer.
    * for real usage see `Engine::Application`s implementation of the
    * main game loop.
    */
  auto deltaProducer = [=](Timestep &ts)
  {
    const Timestep fps{60.0f};
    ts = (fps * 1/1000.f);
  };

  Tester::addTest([=]()
  {
    Timestep t;
    float fps = 60.0f;
    Timestep delta;
    for(int i=0; i<10; ++i){
      deltaProducer(delta);
      t = t + delta;
    }
    Timestep frameTime{1000.f/fps};
    BE_TEST_MULTI(t - (10.0f * frameTime) <= Timestep{0.0001f});
    return test_status::TEST_OK;
  });
}
