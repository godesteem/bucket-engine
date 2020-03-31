//
// Created by phil on 10.03.20.
//
#pragma once
#include <cassert>

enum class test_status
{
  TEST_OK = 0,
};

#ifndef BE_TEST_ASSERT
#define BE_TEST_ASSERT(x) assert(x);
#endif
#define BE_TEST_ERROR(...) ::Engine::Log::GetTestLogger()->error(__VA_ARGS__)
#define BE_TEST_SUCCESS(...) ::Engine::Log::GetTestLogger()->info(__VA_ARGS__)
