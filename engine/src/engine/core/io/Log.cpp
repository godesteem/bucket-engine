#include "bepch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Engine {
  
  std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
  std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
  std::shared_ptr<spdlog::logger> Log::s_TestLogger;

  void Log::Init(){
    spdlog::set_pattern("%^[%T] %n: %v%$");
    s_CoreLogger = spdlog::stdout_color_mt("Engine");
    s_CoreLogger->set_level(spdlog::level::trace);
    s_ClientLogger = spdlog::stdout_color_mt("APP");
    s_ClientLogger->set_level(spdlog::level::trace);
    s_TestLogger = spdlog::stdout_color_mt("Test");
    s_TestLogger->set_level(spdlog::level::trace);

  }
}
