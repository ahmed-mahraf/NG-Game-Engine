
/** @file renderCommand.h
*	header file to set up render commands
*/
#pragma once

#include "rendererAPI.h"

namespace Engine
{
	/** @class RenderCommand
	*	declaration of commands for rendering
	*/
	class RenderCommand
	{
	public:
		inline static void init()
		{
			s_rendererAPI->init();
		}

		inline static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_rendererAPI->setViewport(x, y, width, height);
		}

		inline static void setClearColour(const glm::vec4& rgb)
		{
			s_rendererAPI->setClearColour(rgb);
		}
		inline static void clear()
		{
			s_rendererAPI->clear();
		}

		inline static void drawIndexed(const Ref<VertexArray>& vA)
		{
			s_rendererAPI->drawIndexed(vA);
		}

	private:
		static Scope<RendererAPI> s_rendererAPI;
	};

}