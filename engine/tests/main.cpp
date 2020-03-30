/**
 * File              : main.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 10.03.2020
 * Last Modified Date: 10.03.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include "bepch.h"
#include "test_math.h"

int main(int argc, char **argv){
  Engine::Log::Init();
  test_math();
  matTest();
  return 0;
}
