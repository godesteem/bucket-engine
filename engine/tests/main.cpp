#include "bepch.h"
#include "tests.h"

#include "test_math.h"
#include "core/test_timestep.h"

int main(int argc, char** argv){
  Engine::Log::Init();

  //jnl creates the tests after the static variable holding them is initialized
  //    otherwise the static vector will get initialized after the tests were added and get deleted
  //    that wasnt fun to debug and find, pinpoint and write sample classes to be sure
  TestMath testMath;
  TestTimestep testTimestep;
  // parse args
  bool runAll = argc <= 1;

  if(runAll)
  {
    return ! Tester::executeAll();
  }
  else
  {
    try
    {
      return (Tester::execute(std::stoi(argv[1])) == test_status::TEST_OK ? 0 : 1);
    }
    catch (const std::exception&)
    {
      return 3; // cmdline argument malformed
    }
  }
}
