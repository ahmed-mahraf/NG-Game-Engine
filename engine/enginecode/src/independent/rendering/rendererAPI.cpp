/** @file rendererAPI.cpp
*	create scope from rendererAPI and check if api is supported
*/
#include "engine_pch.h"

#include "rendering/rendererAPI.h"

#include "platforms/openGL/OpenGLRendererAPI.h"

namespace Engine
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	Scope<RendererAPI> RendererAPI::create()
	{
		switch (s_API)
		{
		case RendererAPI::API::None:    GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return createScope<OpenGLRendererAPI>();
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}