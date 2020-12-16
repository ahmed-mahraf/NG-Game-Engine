/** @file OpenGLVertexArray.cpp
*	initialise and created vertex array for opengl functions 
*/
#include "engine_pch.h"
#include "platforms/openGL/OpenGLVertexArray.h"
#include <glad/glad.h>

namespace Engine
{
	//<!for different shader data types, return which GL data type
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:			return GL_FLOAT;
		case ShaderDataType::Float2:		return GL_FLOAT;
		case ShaderDataType::Float3:		return GL_FLOAT;
		case ShaderDataType::Float4:		return GL_FLOAT;
		case ShaderDataType::Mat3:			return GL_FLOAT;
		case ShaderDataType::Mat4:			return GL_FLOAT;
		case ShaderDataType::Int:			return GL_INT;
		case ShaderDataType::Int2:			return GL_INT;
		case ShaderDataType::Int3:			return GL_INT;
		case ShaderDataType::Int4:			return GL_INT;
		case ShaderDataType::Bool:			return GL_BOOL;
		}
		GE_CORE_ASSERT(false, "unknown ShaderDataType");
		return 0;
	}

	//<!constructor for vertex array
	OpenGLVertexArray::OpenGLVertexArray()
	{
		NG_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &m_rendererID);
	}
	//<!deconstructor for vertex array
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		NG_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_rendererID);
	}
	//<!bind vertext array
	void OpenGLVertexArray::bind() const
	{
		NG_PROFILE_FUNCTION();

		glBindVertexArray(m_rendererID);
	}
	//<!unbind vertex array
	void OpenGLVertexArray::unbind() const
	{
		NG_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}
	//<!add vertex buffer to vertex array
	void OpenGLVertexArray::addVertexBuffer(const Ref<VertexBuffer>& vB)
	{
		NG_PROFILE_FUNCTION();

		GE_CORE_ASSERT(vB->getLayout().getElements().size(), "Vertex buffer has no layout!");

		glBindVertexArray(m_rendererID);
		vB->bind();

		uint32_t index = 0;
		const auto& layout = vB->getLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer
			(index,
				element.getComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.getStride(),
				(const void*)element.Offset);
			index++;
		}
		m_VB.push_back(vB);
	}
	//<!set indexbuffer 
	void OpenGLVertexArray::setIndexBuffer(const Ref<IndexBuffer>& iB)
	{
		NG_PROFILE_FUNCTION();

		glBindVertexArray(m_rendererID);
		iB->bind();

		m_IB = iB;
	}
}