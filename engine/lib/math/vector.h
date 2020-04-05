#pragma once

#include "math_headers.h"
#include <cmath>
#include <bepch.h>

// this file can be deleted, serves as reference until then
#if 0
namespace Engine
{
  namespace Math
  {
    struct vec2
    {
      inline explicit vec2() : x(0.0f), y(x) {};
      inline vec2(float __x, float __y) : x(__x), y(__y) {};
      inline explicit vec2(float __x) : x(__x), y(x) {};

      // Constructors
      inline float max() { return std::max<float>(x, y); }

      inline float min() { return std::min(x, y); }

      // Mathematical operators
      inline bool operator==(const vec2 &other) { return x == other.x && y == other.y; }
      inline bool operator!=(const vec2 &other) { return !(*this == other); }

      static inline vec2 Orthogonal() { return {0.0f, 1.0f};}

      // Ostream operator
      inline friend std::ostream &operator<<(std::ostream &ost, const vec2 &vec)
      {
        ost << "(" << vec.x << ", " << vec.y << ")" << std::endl;
        return ost;
      }

      // Members
      float x = 0.0f;
      float y = 0.0f;
    };
    struct vec3 {
      inline explicit vec3() : x(0.0f), y(x), z(y) {};
      inline explicit vec3(float __x) : x(__x), y(x), z(x) {};
      inline vec3(float __x, float __y) : x(__x), y(__y), z(0.0f) {};
      inline vec3(float __x, float __y, float __z) : x(__x), y(__y), z(__z) {};
      static inline vec3 Orthogonal() { return {0.0f, 1.0f, 0.0f};}

      friend std::ostream &operator<<(std::ostream &ost, const vec3 &vec) {
        ost << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;
        return ost;
      }

      float x, y, z;
    };

    float Length(const vec2 &vec){ return sqrtf(SQUARE(vec.x) + SQUARE(vec.y));}
    float Length(const vec3 &vec){ return sqrtf(SQUARE(vec.x) + SQUARE(vec.y) + SQUARE(vec.z));}

    inline float Dot(const vec2 &a, const vec2 &b){return a.x * b.x + a.y * b.y;}
    inline float Dot(const vec3 &a, const vec3 &b){return a.x * b.x + a.y * b.y + a.z * b.z;}

    inline vec3 CrossProduct(vec3 a, vec3 b){return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};}

    template<typename T>
    T Normalize(const T &vec) {

    }
    // Mathematical operators

    inline vec2 operator+(const vec2 &a, const vec2 &b) { return {a.x + b.x, a.y + b.y}; }

    inline float operator*(const vec2 &a, const vec2 &b) { return Dot(a, b); }

    inline vec2 operator*(const vec2 &a, const float &b) { return {a.x * b, a.y * b}; }

  }
}
#endif
