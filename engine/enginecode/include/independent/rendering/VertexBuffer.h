/** @file VertexBuffer.h
*	header file sets up vertex buffer
*/
#pragma once
#include "rendering/BufferLayout.h"

namespace Engine
{
	/**
	* @class VertexBuffer
	* links with openglvertex buffer
	*/
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual const BufferLayout& getLayout() const = 0;
		virtual void setLayout(const BufferLayout& layout) = 0;

		static Ref<VertexBuffer> create(float* vertices, uint32_t size);
	};


}