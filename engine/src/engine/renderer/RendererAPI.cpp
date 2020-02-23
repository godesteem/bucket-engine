/**
 * File              : RendererAPI.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 23.02.2020
 * Last Modified Date: 23.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include "bepch.h"
#include "RendererAPI.h"

namespace Engine {
  
  RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

}
