/**
 * File              : main.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 10.03.2020
 * Last Modified Date: 10.03.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include "bepch.h"
#include "tests.h"

#include "test_math.h"

int main(int argc, char** argv){
  Engine::Log::Init();

  if(argc > 1)
    try
    {
      return Tester::execute(std::stoi(argv[1])) == test_status::TEST_OK;
    }
    catch (const std::exception&)
    {
      return 3; // cmdline argument malformed
    }
  else
    Tester::executeAll(); // for manually debugging failing test
  return 1; // in case no argument gets passed, fail
}
