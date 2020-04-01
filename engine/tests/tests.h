//
// Created by phil on 10.03.20.
//
#pragma once
#include <cassert>

enum class test_status
{
  TEST_OK = 0,
  TEST_FAILED = 1
};

#ifndef BE_TEST_ASSERT
  #define BE_TEST_ASSERT(x, ...) if(x)BE_TEST_SUCCESS(std::to_string(__LINE__) + " " __FUNCTION__ " " + std::string(#x));else{ BE_TEST_ERROR(std::to_string(__LINE__) + " " __FUNCTION__ " " + std::string(#x)); return test_status::TEST_FAILED;}
#endif
#define BE_TEST_ERROR(...) ::Engine::Log::GetTestLogger()->error(__VA_ARGS__)
#define BE_TEST_SUCCESS(...) ::Engine::Log::GetTestLogger()->info(__VA_ARGS__)
