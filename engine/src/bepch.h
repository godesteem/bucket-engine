/**
 * File              : bepch.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 16.02.2020
 * Last Modified Date: 29.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#pragma once
#define GLFW_INCLUDE_NONE
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <array>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "engine/Log.h"

#ifdef BE_PLATFORM_WINDOWS
  #include <Windows.h>
#endif

