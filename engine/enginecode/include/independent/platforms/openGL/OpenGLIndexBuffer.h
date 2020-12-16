#pragma once
/**
* @file OpenGLIndexBuffer.h
* @brief A Header file containing values for index buffer
*/
#include "rendering/IndexBuffer.h"

namespace Engine
{

	/**
	* @class OpenGLIndexBuffer
	*  Allows index buffer
	*/
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);//<! constructor0
		virtual ~OpenGLIndexBuffer();//<! deconstrctor

		virtual void bind() const;
		virtual void unbind() const;

		uint32_t getCount() const { return m_count; } //<! get count 

	private:
		uint32_t m_rendererID;
		uint32_t m_count;

	};
}