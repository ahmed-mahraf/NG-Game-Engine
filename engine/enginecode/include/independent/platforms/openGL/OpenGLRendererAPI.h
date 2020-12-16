#pragma once
/**
* @file rendererAPI.h
* @brief A Header file containing values rendererAPI
*/
#include "rendering/rendererAPI.h"

namespace Engine
{
	/**
	* @class rendererAPI
	*  A API renderer
	*/
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void init() override;
		virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		virtual void setClearColour(const glm::vec4& colour) override; //<! set colour
		virtual void clear() override; //<! clear

		virtual void drawIndexed(const Ref<VertexArray>& vertexArray)override; //<! draw
	};
}

