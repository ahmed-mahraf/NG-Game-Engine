/** @file VertexBuffer.cpp
*	create vertex buffer for opengl processing
*/
#include "engine_pch.h"
#include "rendering/VertexBuffer.h"
#include "rendering/renderer.h"
#include "systems/MyLogger.h"
#include "platforms/openGL/OpenGLVertexBuffer.h"

namespace Engine
{
	//<!create vertex buffer
	Ref<VertexBuffer> VertexBuffer::create(float* vertices, uint32_t size)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::API::None: GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return createRef <OpenGLVertexBuffer>(vertices, size);
		}

		GE_CORE_ASSERT(false, "unknown RendererAPI");
		return nullptr;
	}
}