#pragma once

#include "tests.h"
#include "noise/noise.h"

void TestNoise()
{
  static bool alreadyRan = false;
  if(alreadyRan) return;
  alreadyRan = true;
  using namespace Engine;

  Tester::addTest([=]()
  {
    Engine::Noise::OpenSimplexNoise noise(0);
    Engine::Noise::OpenSimplexNoise noise2(0);
    double value = noise.Evaluate(10.0, 10.0);
    double value2 = noise2.Evaluate(10.0, 10.0);
    BE_TEST_ONCE(value == value2);
  });
  Tester::addTest([=]()
  {
    Engine::Noise::OpenSimplexNoise noise(0);
    Engine::Noise::OpenSimplexNoise noise2(2);
    double value = noise.Evaluate(10.0, 10.0);
    double value2 = noise2.Evaluate(10.0, 10.0);
    BE_TEST_ONCE(value != value2);
  });
  Tester::addTest([=]()
  {
    Engine::Noise::OpenSimplexNoise noise(0);
    Engine::Noise::OpenSimplexNoise noise2(0);
    double value = noise.Evaluate(10.0, 10.0, 10.0);
    double value2 = noise2.Evaluate(10.0, 10.0, 10.0);
    BE_TEST_ONCE(value == value2);
  });
  Tester::addTest([=]()
  {
    Engine::Noise::OpenSimplexNoise noise(0);
    Engine::Noise::OpenSimplexNoise noise2(2);
    double value = noise.Evaluate(10.0, 10.0, 10.0);
    double value2 = noise2.Evaluate(10.0, 10.0, 10.0);
    BE_TEST_ONCE(value != value2);
  });
  Tester::addTest([=]()
  {
    Engine::Noise::OpenSimplexNoise noise(0);
    Engine::Noise::OpenSimplexNoise noise2(0);
    double value = noise.Evaluate(10.0, 10.0, 10.0, 10.0);
    double value2 = noise2.Evaluate(10.0, 10.0, 10.0, 10.0);
    BE_TEST_ONCE(value  == value2);
  });
  Tester::addTest([=]()
  {
    Engine::Noise::OpenSimplexNoise noise(0);
    Engine::Noise::OpenSimplexNoise noise2(2);
    double value = noise.Evaluate(10.0, 10.0, 10.0, 10.0);
    double value2 = noise2.Evaluate(10.0, 10.0, 10.0, 10.0);
    BE_TEST_ONCE(value != value2);
  });
}
