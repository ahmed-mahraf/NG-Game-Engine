/** @file VertexArray.h
*	header file sets up vertex array
*/
#pragma once

#include <memory>

#include "rendering/VertexBuffer.h"
#include "rendering/IndexBuffer.h"

namespace Engine
{
	/**
	* @class VertexArray
	* Links with OpenGLVertexArray
	*/
	class VertexArray
	{

	public:
		virtual ~VertexArray() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& getVertexBuffer() const = 0;
		virtual const Ref<IndexBuffer>& getIndexBuffer() const = 0;


		static Ref<VertexArray> create();

	};
}