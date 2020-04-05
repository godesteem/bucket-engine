#pragma once

#include <memory>
#include <string>
#include <regex>

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
#ifdef BE_PLATFORM_WINDOWS
  static std::string rootDir("D:\\Users\\Joshua\\git\\bucket-engine\\");
  #define ConstructPath(str) std::regex_replace(str, std::regex("/"), "\\")
  #define CONSTRUCT_FILE_PATH(x) std::string(rootDir + ConstructPath(x))
#elif BE_PLATFORM_LINUX
  static std::string rootDir(getenv("ROOT_DIR"));
  #define CONSTRUCT_FILE_PATH(x) std::string(rootDir + x)
#endif
#endif
}




