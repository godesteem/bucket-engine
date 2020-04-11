//
// Created by phil on 28.03.20.
//
#pragma once

#ifndef VM_INLINE
#define VM_INLINE   __forceinline
#endif
#ifndef M_PI
#define M_PI        3.14159265358979323846f
#endif
#ifndef DEG2RAD
#define DEG2RAD(_a) ((_a)*M_PI/180.0f)
#endif
#ifndef RAD2DEG
#define RAD2DEG(_a) ((_a)*180.0f/M_PI)
#endif
#ifndef INT_MIN
#define INT_MIN     (-2147483647 - 1)
#endif
#ifndef INT_MAX
#define INT_MAX     2147483647
#endif
#ifndef FLT_MAX
#define FLT_MAX     3.402823466e+38F
#endif
#ifndef NULL_OR_VAL
#define NULL_OR_VAL_WITH_DEFAULT(__q, __v) (__q == NULL ? __v : __q)
#define NULL_OR_VAL_WITHOUT_DEFAULT(__q) NULL_OR_VAL_WITH_DEFAULT(__q, 0.0f)
#define GET_3RD_ARG(arg1, arg2, arg3, ...) arg3
#define NULL_OR_VAL_MACRO_CHOOSER(...) GET_3RD_ARG(__VA_ARGS__, NULL_OR_VAL_WITH_DEFAULT, NULL_OR_VAL_WITHOUT_DEFAULT, )
#define NULL_OR_VAL(...) NULL_OR_VAL_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)
#endif
#ifndef SQUARE
#define SQUARE(x) pow(x, 2.0f)
#endif
