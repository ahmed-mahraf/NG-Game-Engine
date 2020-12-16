/** @file graphicsContext.h
*	header file includes events
*/

#pragma once

namespace Engine {

	/**
	*@class Interface class for all graphics contexts. Will combine windows tech with graphics API i.e. OPENGLGLFW or WIN32DIRECTX
	* Basically provides means for initialisation and swapchain implementation.
	*/

	class GraphicsContext
	{
	public:
		virtual void init() = 0; //<! function to call init
		virtual void swapBuffers() = 0; //<! function to swap buffers

		static Scope<GraphicsContext> create(void* window); //<! Creates the graphics Context
	};

}

