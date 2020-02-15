/**
 * File              : Core.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 15.02.2020
 * Last Modified Date: 15.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once

#ifdef BE_PLATFORM_WINDOWS
  #define BE_API
#else
  #define BE_API
#endif

#define BIT(x)(1 << x)
