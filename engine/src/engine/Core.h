/**
 * File              : Core.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 15.02.2020
 * Last Modified Date: 29.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once

#include <memory>

#ifdef BE_PLATFORM_WINDOWS
  #define BE_API
  #define NEW_LINE_CHAR "\r\n"
#else
  #define BE_API
  #define NEW_LINE_CHAR "\n"
#endif

#define BIT(x)(1 << x)

#define BE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Engine {
  
  template<typename T>
  using Scope = std::unique_ptr<T>;

  template<typename T>
  using Ref = std::shared_ptr<T>;

  using byte = unsigned char;

#ifndef CONSTRUCT_FILE_PATH
  const std::string rootDir = "/home/philipp/work/priv/bucket-engine/";
  #define CONSTRUCT_FILE_PATH(x) std::string(rootDir + x)
#endif
}
