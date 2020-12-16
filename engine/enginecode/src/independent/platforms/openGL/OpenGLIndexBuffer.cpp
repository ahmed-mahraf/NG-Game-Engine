/** @file OpenGLIndexBuffer.cpp
*	cpp file for the index buffer creation 
*/
#include "engine_pch.h"
#include "platforms/openGL/OpenGLIndexBuffer.h"
#include <glad/glad.h>

namespace Engine
{
	//<!Index Buffer constructor

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) : m_count(count)
	{
		NG_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_rendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}
	//<!index buffer deconstructor
	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		NG_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_rendererID);
	}
	//<!bind index buffer
	void OpenGLIndexBuffer::bind() const
	{
		NG_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
	}
	//<!unbind index buffer
	void OpenGLIndexBuffer::unbind() const
	{
		NG_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}