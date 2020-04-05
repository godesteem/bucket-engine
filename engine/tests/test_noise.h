#pragma once

#include "tests.h"
#include "noise/noise.h"


void TestNoise()
{
  // guard against adding tests twice
  static bool alreadyRan = false;
  if(alreadyRan) return;
  alreadyRan = true;
  using namespace Engine;
  Tester::addTest([=]()
  {
    Engine::Noise::OpenSimplexNoise noise(2);
    double value = noise.Evaluate(1.0, 1.0, 1.0/100);
    BE_TEST_ONCE(value != 0.0f);
  });
}