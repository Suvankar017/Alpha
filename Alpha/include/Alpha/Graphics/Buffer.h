#pragma once

#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>
#include <string>
#include <vector>

#include <spdlog/fmt/ostr.h>

#include "Alpha/Macros.h"

namespace Alpha
{
	///////////////
	// Enums //////
	///////////////

	enum class BufferType : uint32_t
	{
		Stream = 0x88E0,
		Static = 0x88E4,
		Dynamic = 0x88E8
	};

	const char* BufferTypeToString(BufferType type);

	enum class ElementType
	{
		Int, Int2, Int3, Int4, UInt, UInt2, UInt3, UInt4, Float, Float2, Float3, Float4, Double, Double2, Double3, Double4
	};


	////////////////////////
	// Buffer Element //////
	////////////////////////

	struct BufferElement
	{
		std::string Name;
		ElementType Type;
		uint32_t Size;
		uint32_t Offset;
		bool IsNormalized;

		BufferElement(ElementType type, const std::string& name, bool isNormalized = false);

		inline const char* GetTypeName() const { return TypeName(Type); }
		inline uint32_t GetComponentCount() const { return ComponentCount(Type); }
		inline uint32_t ToBaseType() const { return ToBaseType(Type); }

		friend std::ostream& operator<<(std::ostream& os, const BufferElement& e);

		static uint32_t SizeOf(ElementType type);
		static const char* TypeName(ElementType type);
		static uint32_t ComponentCount(ElementType type);
		static uint32_t ToBaseType(ElementType type);
		static const char* BaseTypeName(ElementType type);
	};


	////////////////////////
	// Buffer Layout ///////
	////////////////////////

	class BufferLayout
	{
	public:
		BufferLayout();
		BufferLayout(const std::initializer_list<BufferElement>& elements);

		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		const std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		const std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

		friend std::ostream& operator<<(std::ostream& os, const BufferLayout& l);

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride;

		void CalcStrideAndOffset()
		{
			for (BufferElement& e : m_Elements)
			{
				e.Offset = m_Stride;
				m_Stride += e.Size;
			}
		}
	};


	////////////////////////
	// Vertex Buffer ///////
	////////////////////////

	class VertexBuffer;
	DEF_SMART_POINTER(VertexBuffer);

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual BufferType GetBufferType() const = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		virtual void SetData(uint32_t offset, size_t size, const void* data) = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		friend std::ostream& operator<<(std::ostream& os, const VertexBuffer& vbo) { return vbo.ToOutStream(os, vbo); }

		static VertexBuffer* Create(size_t size, const void* data, BufferType bufferType = BufferType::Static);
		static VertexBufferScope CreateScope(size_t size, const void* data, BufferType bufferType = BufferType::Static);
		static VertexBufferRef CreateRef(size_t size, const void* data, BufferType bufferType = BufferType::Static);
		static void Destroy(VertexBuffer*& buffer);

	protected:
		virtual std::ostream& ToOutStream(std::ostream& os, const VertexBuffer& vbo) const { return os << "Base-VBO"; }
	};


	////////////////////////
	// Index Buffer ////////
	////////////////////////

	class IndexBuffer;
	DEF_SMART_POINTER(IndexBuffer);

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual BufferType GetBufferType() const = 0;
		virtual uint32_t GetCount() const = 0;

		virtual void SetData(uint32_t offset, size_t size, const uint32_t* data) = 0;

		friend std::ostream& operator<<(std::ostream& os, const IndexBuffer& ibo) { return ibo.ToOutStream(os, ibo); }

		static IndexBuffer* Create(size_t size, const uint32_t* data, uint32_t count = 0U, BufferType type = BufferType::Static);
		static IndexBufferScope CreateScope(size_t size, const uint32_t* data, uint32_t count = 0U, BufferType type = BufferType::Static);
		static IndexBufferRef CreateRef(size_t size, const uint32_t* data, uint32_t count = 0U, BufferType type = BufferType::Static);
		static void Destroy(IndexBuffer*& buffer);

	protected:
		virtual std::ostream& ToOutStream(std::ostream& os, const IndexBuffer& ibo) const { return os << "Base-IBO"; }
	};

}

#endif // !BUFFER_H
