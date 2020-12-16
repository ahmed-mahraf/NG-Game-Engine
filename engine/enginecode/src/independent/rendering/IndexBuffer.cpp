/** @file IndexBuffer.cpp
* create index buffer
*/
#include "engine_pch.h"
#include "rendering/IndexBuffer.h"
#include "rendering/renderer.h"
#include "systems/MyLogger.h"
#include "platforms/openGL/OpenGLIndexBuffer.h"

namespace Engine
{
	//<!return index buffer size
	Ref<IndexBuffer> IndexBuffer::create(uint32_t* indices, uint32_t size)
	{
		{
			switch (Renderer::getAPI())
			{
			case RendererAPI::API::None: GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return createRef <OpenGLIndexBuffer>(indices, size);
			}

			GE_CORE_ASSERT(false, "unknown RendererAPI");
			return nullptr;
		}
	}
}