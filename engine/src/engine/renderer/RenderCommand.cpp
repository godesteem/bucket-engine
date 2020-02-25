/**
 * File              : RenderCommand.cpp
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 23.02.2020
 * Last Modified Date: 25.02.2020
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
#include "bepch.h"
#include "RenderCommand.h"

#include "platform/opengl/OpenGLRendererAPI.h"

namespace Engine {
  RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}
