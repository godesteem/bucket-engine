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
  // CORE LOG MACROS
  #define BE_CORE_ERROR(...) ::Engine::Log::GetCoreLogger()->error(__VA_ARGS__)
  #define BE_CORE_WARN(...) ::Engine::Log::GetCoreLogger()->warn(__VA_ARGS__)
  #define BE_CORE_TRACE(...) ::Engine::Log::GetCoreLogger()->trace(__VA_ARGS__)
  #define BE_CORE_INFO(...) ::Engine::Log::GetCoreLogger()->info(__VA_ARGS__)
  #define BE_CORE_FATAL(...) ::Engine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

  // CLIENT LOG MACROS
  #define BE_ERROR(...) ::Engine::Log::GetClientLogger()->error(__VA_ARGS__)
  #define BE_WARN(...) ::Engine::Log::GetClientLogger()->warn(__VA_ARGS__)
  #define BE_TRACE(...) ::Engine::Log::GetClientLogger()->trace(__VA_ARGS__)
  #define BE_INFO(...) ::Engine::Log::GetClientLogger()->info(__VA_ARGS__)
  #define BE_FATAL(...) ::Engine::Log::GetClientLogger()->fatal(__VA_ARGS__)
#else
  // CORE LOG MACROS
  #define BE_CORE_ERROR
  #define BE_CORE_WARN
  #define BE_CORE_TRACE
  #define BE_CORE_INFO
  #define BE_CORE_FATAL

  // CLIENT LOG MACROS
  #define BE_ERROR
  #define BE_WARN
  #define BE_TRACE
  #define BE_INFO
  #define BE_FATAL
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
