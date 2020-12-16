#pragma once
/**
* @file OpenGLVertexBuffer.h
* A Header file containing values for vertex buffer
*/
#include "rendering/VertexBuffer.h"
#include "rendering/BufferLayout.h"

namespace Engine
{
	/**
	* @class OpenGLVertexArray
	* Creates shared pointer to vertex buffer
	*/
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);	//<! constructor
		virtual ~OpenGLVertexBuffer();//<! deconstructor

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual const BufferLayout& getLayout() const override { return m_layout; } //<! get layout
		virtual void setLayout(const BufferLayout& layout) override { m_layout = layout; }//<! set layout

	private:
		uint32_t m_rendererID;
		BufferLayout m_layout;
	};
}