/** @file BufferLayout.h
*	header file includes definitions for buffer layout
*/
#pragma once

//#include "core/base.h" // DO NOT DELETE!

namespace Engine
{
	/** @class ShaderDataType
	*	gets shader data type based on size
	*/
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:		return 4;
			case ShaderDataType::Float2:	return 4 * 2;
			case ShaderDataType::Float3:	return 4 * 3;
			case ShaderDataType::Float4:	return 4 * 4;
			case ShaderDataType::Mat3:		return 4 * 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4 * 4;
			case ShaderDataType::Int:		return 4;
			case ShaderDataType::Int2:		return 4 * 2;
			case ShaderDataType::Int3:		return 4 * 3;
			case ShaderDataType::Int4:		return 4 * 4;
			case ShaderDataType::Bool:		return 1;

		}

		GE_CORE_ASSERT(false, "unknown ShaderDataType");
		return 0;
	}

	struct BufferElement
	{

		
		std::string Name;
		uint32_t Size;
		size_t Offset;
		ShaderDataType Type;
		bool Normalized;

		BufferElement() = default;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0)
		{

		}

		//<! get component for shader data type
		uint32_t getComponentCount() const
			{
				switch (Type)
				{
				case ShaderDataType::Float:		return 1;
				case ShaderDataType::Float2:	return 2;
				case ShaderDataType::Float3:	return 3;
				case ShaderDataType::Float4:	return 4;
				case ShaderDataType::Mat3:		return 3 * 3;
				case ShaderDataType::Mat4:		return 4 * 4;
				case ShaderDataType::Int:		return 1;
				case ShaderDataType::Int2:		return 2;
				case ShaderDataType::Int3:		return 3;
				case ShaderDataType::Int4:		return 4;
				case ShaderDataType::Bool:		return 1;
				}
				GE_CORE_ASSERT(false, "unknown ShaderDataType");
				return 0;
			}
		
	};

	/** @class buffer layout
	*	gets buffer elements
	*/
	class BufferLayout
	{
	public:
		BufferLayout() = default;
		BufferLayout(std::initializer_list<BufferElement> elements) : m_elements(elements) 
		{
			calculateOffsetAndStride();
		}

		uint32_t getStride() const { return m_stride; }
		inline const std::vector<BufferElement>& getElements() const { return m_elements; }

		std::vector < BufferElement >::iterator begin() { return m_elements.begin(); }
		std::vector < BufferElement >::iterator end() { return m_elements.end(); }

		std::vector < BufferElement >::const_iterator begin() const { return m_elements.begin(); }
		std::vector < BufferElement >::const_iterator end() const { return m_elements.end(); }

	private:
		void calculateOffsetAndStride()
		{
			size_t offset = 0;
			m_stride = 0;
			for (auto& element : m_elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_elements;
		uint32_t m_stride = 0;
	};

}
