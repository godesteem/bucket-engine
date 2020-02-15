/**
 * File              : Log.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 15.02.2020
 * Last Modified Date: 15.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"

namespace Engine {
  class Log 
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
