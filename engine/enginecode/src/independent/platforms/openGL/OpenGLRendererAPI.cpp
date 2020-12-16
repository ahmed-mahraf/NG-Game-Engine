/** @file OpenGLRendererAPI.cpp
*	cpp file for setup rendering API and opengl commands using functions created 
*/
#include "engine_pch.h"
#include "platforms/openGL/OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Engine
{
	//<!setup blending
	void OpenGLRendererAPI::init()
	{
		NG_PROFILE_FUNCTION();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}
	//<!set clear colour on render api
	void OpenGLRendererAPI::setClearColour(const glm::vec4 & colour)
	{
		glClearColor(colour.r, colour.g, colour.b, colour.a);
	}
	//<!clear renderer
	void OpenGLRendererAPI::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	//<!draw tringle with renderer
	void OpenGLRendererAPI::drawIndexed(const Ref<VertexArray>& vA)
	{
		glDrawElements(GL_TRIANGLES, vA->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}