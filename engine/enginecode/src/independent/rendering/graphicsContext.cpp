/** @file graphicsContext.cpp
*	create graphics context 
*/
#include "engine_pch.h"
#include "rendering/graphicsContext.h"

#include "rendering/renderer.h"
#include "platforms/openGL/OpenGLGraphicsContext.h"

namespace Engine {

	Scope<GraphicsContext> GraphicsContext::create(void* window)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::API::None:    GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_unique<OpenGLGraphicsContext>(static_cast<GLFWwindow*>(window));
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}