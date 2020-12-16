/** @file OpenGLVertexBuffer.cpp
*   creation for vertex buffer for opengl functions as well as binding and unbinding 
*/
#include "engine_pch.h"
#include "platforms/openGL/OpenGLVertexBuffer.h"
#include <glad/glad.h>

namespace Engine
{
	//<!vertex Buffer constructor
	OpenGLVertexBuffer::OpenGLVertexBuffer(float * vertices, uint32_t size)
	{
		NG_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
	//<!vertex buffer deconstructor
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		NG_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_rendererID);
	}
	//<!bind vertex buffer
	void OpenGLVertexBuffer::bind() const
	{
		NG_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
	}
	//<!unbind vertex buffer
	void OpenGLVertexBuffer::unbind() const
	{
		NG_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}