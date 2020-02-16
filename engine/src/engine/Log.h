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
    
    private:
      static std::shared_ptr<spdlog::logger> s_CoreLogger;
      static std::shared_ptr<spdlog::logger> s_ClientLogger;
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
