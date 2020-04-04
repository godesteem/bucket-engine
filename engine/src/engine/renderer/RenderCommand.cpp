#include "bepch.h"
#include "RenderCommand.h"

#include "platform/opengl/OpenGLRendererAPI.h"

namespace Engine {
  RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}
