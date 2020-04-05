#pragma once

#include "tests.h"
#include "noise/noise.h"

const double NOISE_PRECISION_EPS = 1e-50;


void TestNoise()
{
  static bool alreadyRan = false;
  if(alreadyRan) return;
  alreadyRan = true;
  using namespace Engine;

  Tester::addTest([=]()
  {
    Engine::Noise::OpenSimplexNoise noise(0);
    double value = noise.Evaluate(0.0, 0.0);
    BE_TEST_ONCE(value == 0.0f);
  });
  Tester::addTest([=]()
  {
    Engine::Noise::OpenSimplexNoise noise(0);
    double value = noise.Evaluate(1.0, 0.0);
    BE_TEST_ONCE(value != 0.0f);
  });
  Tester::addTest([=]()
  {
    Engine::Noise::OpenSimplexNoise noise(0);
    double value = noise.Evaluate(0.0, 0.0, 0.0);
    BE_TEST_ONCE(fabs(value) < NOISE_PRECISION_EPS);
  });
  Tester::addTest([=]()
  {
    Engine::Noise::OpenSimplexNoise noise(0);
    double value = noise.Evaluate(1.0, 0.0, 0.0);
    BE_TEST_ONCE(value != 0.0f);
  });
  Tester::addTest([=]()
  {
    Engine::Noise::OpenSimplexNoise noise(0);
    double value = noise.Evaluate(0.0, 0.0, 0.0, 0.0);
    BE_TEST_ONCE(fabs(value) < NOISE_PRECISION_EPS);
  });
  Tester::addTest([=]()
  {
    Engine::Noise::OpenSimplexNoise noise(0);
    double value = noise.Evaluate(1.0, 0.0, 0.0, 0.0);
    BE_TEST_ONCE(value != 0.0f);
  });
  Tester::addTest([=]()
  {
    Engine::Noise::OpenSimplexNoise noise(0);
    Engine::Noise::OpenSimplexNoise noise2(0);
    double value = noise.Evaluate(0.0, 0.0, 0.0);
    double value2 = noise2.Evaluate(0.0, 0.0, 0.0);
    BE_TEST_ONCE(value - value2 == 0.0);
  });
  Tester::addTest([=]()
  {
    Engine::Noise::OpenSimplexNoise noise(0);
    double noiseEval2D = noise.Evaluate(0.0, 0.0) / (float)(1.0 / 47.0);
    double noiseEval3D = noise.Evaluate(0.0, 0.0, 0.0) / (float)(1.0 / 103.0);
    double noiseEval4D = noise.Evaluate(0.0, 0.0, 0.0, 0.0) / (float)(1.0 / 30.0);
    BE_TEST_ONCE(fabs(noiseEval2D - noiseEval3D - noiseEval4D) < NOISE_PRECISION_EPS);
  });
}
