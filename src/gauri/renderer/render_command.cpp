#include "grpch.h"

#include "gauri/renderer/render_command.h"

#include "platform/opengl/opengl_renderer_api.h"

namespace gauri
{
RendererAPI *RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}
