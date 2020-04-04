//
// Created by phil on 10.03.20.
//
#pragma once
#include <cassert>

enum class test_status
{
  TEST_OK = 0,
  TEST_FAILED = 1,
  TEST_NOT_FOUND,
};

#ifndef BE_TEST_ASSERT
  // will exit on test_fail, continue on test_ok
  #define BE_TEST_MULTI(x, ...) \
  if(x)\
  {\
    BE_TEST_SUCCESS(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " " + std::string(#x));\
  }\
  else\
  {\
    BE_TEST_ERROR(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " " + std::string(#x));\
    return test_status::TEST_FAILED;\
  }

  // will exit on both test_fail and on test_ok
  #define BE_TEST_ONCE(x, ...) \
  if(x)\
  {\
    BE_TEST_SUCCESS(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " " + std::string(#x));\
   return test_status::TEST_OK;\
  }\
  else\
  {\
    BE_TEST_ERROR(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " " + std::string(#x));\
    return test_status::TEST_FAILED;\
  }

#endif
#define BE_TEST_ERROR(...) ::Engine::Log::GetTestLogger()->error(__VA_ARGS__)
#define BE_TEST_SUCCESS(...) ::Engine::Log::GetTestLogger()->info(__VA_ARGS__)


#include <vector>
#include <iterator>
#include <functional>

// wont remove duplicates
class Tester
{
private:
  typedef std::function<test_status()> test_func_pointer;
  static std::vector<test_func_pointer> tests;
public:

  Tester(test_func_pointer const& newTest)
  {
    addTest(newTest);
  }
  ~Tester() = default;

  static test_status execute(int testNum)
  {
    if(testNum < 0 || testNum >= Tester::tests.size())
      return test_status::TEST_NOT_FOUND;
    auto toCallIt = Tester::tests.begin(); // iterator to first test
    std::advance(toCallIt, testNum); // find test to call
    return (*toCallIt)(); // call it
  }

  // to debug a failing test via breakpoints:
  // returns if all have passed
  static bool executeAll()
  {
    bool allPassed = true;
    for (auto const& test : Tester::tests)
      allPassed &= (test() == test_status::TEST_OK);
    return allPassed;
  }

  static void addTest(test_func_pointer const& newTest)
  {
    Tester::tests.push_back(newTest);
  }

  static size_t Count(){return Tester::tests.size();}
};
