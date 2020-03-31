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
  bool all_ok = true;
  all_ok &= test_vec2() == test_status::TEST_OK;
  all_ok &= test_mat2() == test_status::TEST_OK;
  all_ok &= matTest() == test_status::TEST_OK;
  return (all_ok ? 0 : 1);
}
