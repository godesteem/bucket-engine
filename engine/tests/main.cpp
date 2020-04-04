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

[[nodiscard]] int foo()
{
  return 1;
}

int main(int argc, char** argv){
  Engine::Log::Init();


  foo();

  return 0;

  //jnl creates the tests after the static variable holding them is initialized
  //    otherwise the static vector will get initialized after the tests were added and get deleted
  //    that wasnt fun to debug and find, pinpoint and write sample classes to be sure
  TestMath instance;

  if(argc > 1)
    try
    {
      return (Tester::execute(std::stoi(argv[1])) == test_status::TEST_OK ? 0 : 1);
    }
    catch (const std::exception&)
    {
      return 3; // cmdline argument malformed
    }
  else
    return Tester::executeAll(); // for manually debugging failing test
  return 2; // in case no argument gets passed, fail
}
