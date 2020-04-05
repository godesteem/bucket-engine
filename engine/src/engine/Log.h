/**
 * File              : Log.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 15.02.2020
 * Last Modified Date: 16.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Engine {
  class BE_API Log
  {
    public:
      static void Init();

      inline static std::shared_ptr<spdlog::logger> &GetCoreLogger(){return s_CoreLogger;};
      inline static std::shared_ptr<spdlog::logger> &GetClientLogger(){return s_ClientLogger;};
      inline static std::shared_ptr<spdlog::logger> &GetTestLogger(){return s_TestLogger;};

    private:
      static std::shared_ptr<spdlog::logger> s_CoreLogger;
      static std::shared_ptr<spdlog::logger> s_ClientLogger;
      static std::shared_ptr<spdlog::logger> s_TestLogger;
  };
}

#ifdef BE_DEBUG
  // CORE LOG FUNCTIONS
  template <typename T, typename ... P>
  void BE_CORE_ERROR(const T& t, const P& ... p)
  { Engine::Log::GetCoreLogger()->error(t, p...); }
  template <typename T, typename ... P>
  void BE_CORE_WARN(const T& t, const P& ... p)
  { Engine::Log::GetCoreLogger()->warn(t, p...); }
  template <typename T, typename ... P>
  void BE_CORE_TRACE(const T& t, const P& ... p)
  { Engine::Log::GetCoreLogger()->trace(t, p...); }
  template <typename T, typename ... P>
  void BE_CORE_INFO(const T& t, const P& ... p)
  { Engine::Log::GetCoreLogger()->info(t, p...); }
  template <typename T, typename ... P>
  void BE_CORE_FATAL(const T& t, const P& ... p)
  { Engine::Log::GetCoreLogger()->fatal(t, p...); }

  // CLIENT LOG FUNCTIONS
  template <typename T, typename ... P>
  void BE_ERROR(const T& t, const P& ... p)
  { Engine::Log::GetClientLogger()->error(t, p...); }
  template <typename T, typename ... P>
  void BE_WARN(const T& t, const P& ... p)
  { Engine::Log::GetClientLogger()->warn(t, p...); }
  template <typename T, typename ... P>
  void BE_TRACE(const T& t, const P& ... p)
  { Engine::Log::GetClientLogger()->trace(t, p...); }
  template <typename T, typename ... P>
  void BE_INFO(const T& t, const P& ... p)
  { Engine::Log::GetClientLogger()->info(t, p...); }
  template <typename T, typename ... P>
  void BE_FATAL(const T& t, const P& ... p)
  { Engine::Log::GetClientLogger()->fatal(t, p...); }
#else
  // CORE LOG FUNCTIONS
  template <typename T, typename ... P>
  void BE_CORE_ERROR(const T& t, const P& ... p) { }
  template <typename T, typename ... P>
  void BE_CORE_WARN(const T& t, const P& ... p) { }
  template <typename T, typename ... P>
  void BE_CORE_TRACE(const T& t, const P& ... p) { }
  template <typename T, typename ... P>
  void BE_CORE_INFO(const T& t, const P& ... p) { }
  template <typename T, typename ... P>
  void BE_CORE_FATAL(const T& t, const P& ... p) { }

  // CLIENT LOG FUNCTIONS
  template <typename T, typename ... P>
  void BE_ERROR(const T& t, const P& ... p) { }
  template <typename T, typename ... P>
  void BE_WARN(const T& t, const P& ... p) { }
  template <typename T, typename ... P>
  void BE_TRACE(const T& t, const P& ... p) { }
  template <typename T, typename ... P>
  void BE_INFO(const T& t, const P& ... p) { }
  template <typename T, typename ... P>
  void BE_FATAL(const T& t, const P& ... p) { }
#endif

#ifndef BE_ENABLE_ASSERTS
  #ifdef BE_PLATFORM_WINDOWS
    #include <WinBase.h>
    #define BE_ASSERT(x, ... ) { if(!(x)){BE_ERROR("Assertion failed: {0}", __VA_ARGS__); DebugBreak();} }
    #define BE_CORE_ASSERT(x, ... ) { if(!(x)){BE_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); DebugBreak();} }
  #elif BE_PLATFORM_LINUX
    #define BE_ASSERT(x, ... ) { if(!(x)){BE_ERROR("Assertion failed: {0}", __VA_ARGS__); __builtin_trap();} }
    #define BE_CORE_ASSERT(x, ... ) { if(!(x)){BE_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __builtin_trap();} }
  #endif
  #define BE_CHECK_FILE(x, y, ... ) {auto l = x.find_last_of("/\\"); \
                                      l = l == std::string::npos ? 0 : l + 1; \
                                      auto lDot = x.rfind('.'); \
                                      std::ostringstream stringStream; \
                                      stringStream << "Wrong file extension \"" << \
                                      x.substr(lDot, x.size()) << "\". Need " << y << "!"; \
                                      std::string copyOfStr = stringStream.str(); \
                                      BE_CORE_ASSERT(x.substr(lDot, x.size()) == y, copyOfStr); }
#else
  #define BE_ASSERT(x, ... )
  #define BE_CORE_ASSERT(x, ... )
#endif
