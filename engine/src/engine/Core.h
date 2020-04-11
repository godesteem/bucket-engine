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

namespace Engine {
//jnl from http://blog.bitwigglers.org/using-enum-classes-as-type-safe-bitmasks/
//    this enables us to use a type-safe bitmask with enum class
  template<typename Enum>
  struct EnableBitMaskOperators {
    static const bool enable = false;
  };

  template<typename Enum>
  typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
  operator|(Enum lhs, Enum rhs) {
    using underlying = typename std::underlying_type<Enum>::type;
    return static_cast<Enum> (
        static_cast<underlying>(lhs) |
        static_cast<underlying>(rhs)
    );
  }

  template<typename Enum>
  typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
  operator&(Enum lhs, Enum rhs) {
    using underlying = typename std::underlying_type<Enum>::type;
    return static_cast<Enum> (
        static_cast<underlying>(lhs) &
        static_cast<underlying>(rhs)
    );
  }

  #define ENABLE_BITMASK_OPERATORS(x)  \
  template<>                           \
  struct EnableBitMaskOperators<x>     \
  {                                    \
    static const bool enable = true; \
  };
}
