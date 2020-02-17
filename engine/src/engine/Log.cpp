/**
 * File              : Log.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 15.02.2020
 * Last Modified Date: 17.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include "bepch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Engine {
  
  std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
  std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
  
  void Log::Init(){
    spdlog::set_pattern("%^[%T] %n: %v%$");
    s_CoreLogger = spdlog::stdout_color_mt("Engine");
    s_CoreLogger->set_level(spdlog::level::trace);
    s_ClientLogger = spdlog::stdout_color_mt("APP");
    s_ClientLogger->set_level(spdlog::level::trace);

  }
}
