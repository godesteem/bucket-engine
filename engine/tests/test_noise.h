#pragma once

#include "tests.h"
#include "noise/noise.h"


bool test_OpenSimplexNoise(){
  Engine::Noise::OpenSimplexNoise noise(2);
  double value = noise.Evaluate(1.0, 1.0, 1.0/100);
  BE_TEST_ASSERT(value != 0.0);

  return TEST_OK;
}

void test_noise(){
  if(test_OpenSimplexNoise() != TEST_OK) BE_TEST_ERROR( "OpenSimplexNoise not working!");
  else BE_TEST_SUCCESS( "OpenSimplexNoise is working.");
}