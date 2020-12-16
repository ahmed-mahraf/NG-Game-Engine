/** @file VertexArray.cpp
*	vertex array creation 
*/
#include "engine_pch.h"
#include "rendering/VertexArray.h"

#include "rendering/renderer.h"
#include "platforms/openGL/OpenGLVertexArray.h"

namespace Engine
{
	//<!create vertex array
	Ref<VertexArray> VertexArray::create()
	{

		switch (Renderer::getAPI())
		{
		case RendererAPI::API::None: GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return createRef<OpenGLVertexArray>();
		}

		GE_CORE_ASSERT(false, "unknown RendererAPI");
		return nullptr;

	}
}
