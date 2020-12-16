/** @file Texture.cpp
*	create 2d textures 
*/
#include "engine_pch.h"
#include "rendering/Texture.h"

#include "rendering/renderer.h"
#include "platforms/openGL/OpenGLTexture.h"

namespace Engine {

	Ref<Texture2D> Texture2D::create(uint32_t width, uint32_t height)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::API::None:    GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return createRef<OpenGLTexture2D>(width, height);
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	std::shared_ptr<Texture2D> Texture2D::create(const std::string& path)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::API::None: GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return createRef<OpenGLTexture2D>(path);
		}

		GE_CORE_ASSERT(false, "unknown RendererAPI");
		return nullptr;
	}
}