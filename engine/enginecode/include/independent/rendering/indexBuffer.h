/** @file indexBuffer.h
*	sets up values for index buffer
*/

#pragma once

namespace Engine
{
	/**
	*	@class IndexBuffer
	*	variables to be used by index buffer
	*
	*/

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual uint32_t getCount() const = 0;

		static Ref<IndexBuffer> create(uint32_t* indices, uint32_t size);
	};


}