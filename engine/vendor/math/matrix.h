/**
 * File              : matrix.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 10.03.2020
 * Last Modified Date: 10.03.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once

#include "vector.h"

namespace Engine {
  namespace Math {
    struct mat2 {
      inline mat2(float a11, float a12, float a21, float a22): u({a11, a12}), v({a21, a22}){};
      inline mat2(vec2 _u, vec2 _v): u(_u), v(_v){};
      inline explicit mat2(float x): u(x), v(x){};

      inline static mat2 Entity() {return {1.0f, 0.0f, 0.0f, 1.0f};}

      // dimension is always given, minimum requirement is equality of elements
      inline bool operator==(const mat2& other){return u == other.u && v == other.v;};
      // A * x = b
      inline mat2 operator*(float other){return {u.x * other, u.y * other, v.x * other, v.y * other};};
      inline mat2 operator*(const mat2& other){return {u.x * other.u.x + u.y * other.v.x, u.x * other.u.y + u.y * other.v.y,v.x * other.u.x + v.y * other.v.x, v.x * other.u.y + v.y * other.v.y};};
      friend inline vec2 operator*(const mat2 &a, const vec2 &b) { return {a.u.x*b.x + a.u.y*b.y,a.v.x*b.x + a.v.y*b.y};}
      vec2 u;
      vec2 v;
    };
  }
}