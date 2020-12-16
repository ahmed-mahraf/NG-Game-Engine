#pragma once
/**
* @file GLFWGraphicsContext.h
* A Header file containing graphics context
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "rendering/graphicsContext.h"

struct GLFWwindow;

namespace Engine
{
	/**
	* @class OpenGL_GLFWGraphicsContext
	*  Provides the values for the GLFW graphics context
	*/
	class OpenGLGraphicsContext : public GraphicsContext
	{
	public:
		OpenGLGraphicsContext(GLFWwindow * windowHandle); //<! constructor
		void init() override; //<! init function
		void swapBuffers()override; //<! swaps the buffers
	private:
		GLFWwindow* m_windowHandle; //<! glfw window pointer to m_window
	};
}
