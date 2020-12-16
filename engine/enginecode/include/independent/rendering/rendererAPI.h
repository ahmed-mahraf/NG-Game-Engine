/** @file rendererAPI.h
*	header file for rednering API use
*/
#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Engine
{
	/** @class RendererAPI
	*	functions and variables for API renderer
	*/
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, 
			OpenGL = 1
		};
	public:
		virtual void init() = 0; //<! Function to call init
		virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0; //<! Function to call init
		virtual void setClearColour(const glm::vec4& colour) = 0; //<! Function to call init
		virtual void clear() = 0; //<! Function to call init

		virtual void drawIndexed(const Ref<VertexArray>& vertexArray) = 0; //<! Function to call init

		inline static API getAPI() { return s_API; } //<! Function to get the API which returns the API value
		
		static Scope<RendererAPI> create();

	private:
		static API s_API; //<! API callback
	};
}