#pragma once
/**
* @file OpenGLVertexArray.h
* A Header file containing values for vertex array
*/
#include "rendering/VertexArray.h"
#include "rendering/IndexBuffer.h"

namespace Engine
{
	/**
	* @class OpenGLVertexArray
	*  Creates shared pointer to vertex array
	*/
	class OpenGLVertexArray : public VertexArray
	{

	public:
		OpenGLVertexArray();//<! constructor
		virtual ~OpenGLVertexArray();//<!deconstructor

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)  override;//<! add vertex array
		virtual void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer)  override;//<! add index buffer 

		virtual const std::vector<Ref<VertexBuffer>>& getVertexBuffer() const { return m_VB; }//<! shared pointer get vertex buffer
		virtual const Ref<IndexBuffer>& getIndexBuffer() const { return m_IB; }//<! shared pointer get index buffer

	private:
		std::vector<Ref<VertexBuffer>> m_VB;//<! shared pointer vertex buffer
		Ref<IndexBuffer> m_IB;//<! shared pointer index buffer
		uint32_t m_rendererID;

	};
}