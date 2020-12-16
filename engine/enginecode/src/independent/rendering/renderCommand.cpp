/** @file renderCommand.cpp
*	create render api
*/
#include "engine_pch.h"

#include "rendering/renderCommand.h"

#include "platforms/openGL/OpenGLRendererAPI.h"

namespace Engine
{
	Scope<RendererAPI> RenderCommand::s_rendererAPI = RendererAPI::create();
}
