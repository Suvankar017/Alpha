#include "pch.h"
#include "Alpha/Graphics/Buffer.h"

#include <glad/glad.h>

namespace Alpha
{
	///////////////
	// Enums //////
	///////////////
	
	const char* BufferTypeToString(BufferType type)
	{
		switch (type)
		{
			case Alpha::BufferType::Stream:		return "Stream";
			case Alpha::BufferType::Static:		return "Static";
			case Alpha::BufferType::Dynamic:	return "Dynamic";
		}

		return nullptr;
	}


	////////////////////////
	// Buffer Element //////
	////////////////////////

	BufferElement::BufferElement(ElementType type, const std::string& name, bool isNormalized) :
		Name(name), Type(type), Size(SizeOf(type)), Offset(0), IsNormalized(isNormalized)
	{
	}

	std::ostream& operator<<(std::ostream& os, const BufferElement& e)
	{
		return os << "(Name : " << e.Name << ", Type : " << e.GetTypeName() << ", Size : " << e.Size << ", Offset : " << e.Offset << ")";
	}

	uint32_t BufferElement::SizeOf(ElementType type)
	{
		switch (type)
		{
			case Alpha::ElementType::Int:		return sizeof(int);
			case Alpha::ElementType::Int2:		return sizeof(int) * 2;
			case Alpha::ElementType::Int3:		return sizeof(int) * 3;
			case Alpha::ElementType::Int4:		return sizeof(int) * 4;
			case Alpha::ElementType::UInt:		return sizeof(unsigned int);
			case Alpha::ElementType::UInt2:		return sizeof(unsigned int) * 2;
			case Alpha::ElementType::UInt3:		return sizeof(unsigned int) * 3;
			case Alpha::ElementType::UInt4:		return sizeof(unsigned int) * 4;
			case Alpha::ElementType::Float:		return sizeof(float);
			case Alpha::ElementType::Float2:	return sizeof(float) * 2;
			case Alpha::ElementType::Float3:	return sizeof(float) * 3;
			case Alpha::ElementType::Float4:	return sizeof(float) * 4;
			case Alpha::ElementType::Double:	return sizeof(double);
			case Alpha::ElementType::Double2:	return sizeof(double) * 2;
			case Alpha::ElementType::Double3:	return sizeof(double) * 3;
			case Alpha::ElementType::Double4:	return sizeof(double) * 4;
		}

		return 0U;
	}

	const char* BufferElement::TypeName(ElementType type)
	{
		switch (type)
		{
			case Alpha::ElementType::Int:		return "Int";
			case Alpha::ElementType::Int2:		return "Int2";
			case Alpha::ElementType::Int3:		return "Int3";
			case Alpha::ElementType::Int4:		return "Int4";
			case Alpha::ElementType::UInt:		return "UInt";
			case Alpha::ElementType::UInt2:		return "UInt2";
			case Alpha::ElementType::UInt3:		return "UInt3";
			case Alpha::ElementType::UInt4:		return "UInt4";
			case Alpha::ElementType::Float:		return "Float";
			case Alpha::ElementType::Float2:	return "Float2";
			case Alpha::ElementType::Float3:	return "Float3";
			case Alpha::ElementType::Float4:	return "Float4";
			case Alpha::ElementType::Double:	return "Double";
			case Alpha::ElementType::Double2:	return "Double2";
			case Alpha::ElementType::Double3:	return "Double3";
			case Alpha::ElementType::Double4:	return "Double4";
		}

		return nullptr;
	}

	uint32_t BufferElement::ComponentCount(ElementType type)
	{
		switch (type)
		{
			case Alpha::ElementType::Int:		return 1U;
			case Alpha::ElementType::Int2:		return 2U;
			case Alpha::ElementType::Int3:		return 3U;
			case Alpha::ElementType::Int4:		return 4U;
			case Alpha::ElementType::UInt:		return 1U;
			case Alpha::ElementType::UInt2:		return 2U;
			case Alpha::ElementType::UInt3:		return 3U;
			case Alpha::ElementType::UInt4:		return 4U;
			case Alpha::ElementType::Float:		return 1U;
			case Alpha::ElementType::Float2:	return 2U;
			case Alpha::ElementType::Float3:	return 3U;
			case Alpha::ElementType::Float4:	return 4U;
			case Alpha::ElementType::Double:	return 1U;
			case Alpha::ElementType::Double2:	return 2U;
			case Alpha::ElementType::Double3:	return 3U;
			case Alpha::ElementType::Double4:	return 4U;
		}

		return 0U;
	}

	uint32_t BufferElement::ToBaseType(ElementType type)
	{
		switch (type)
		{
			case Alpha::ElementType::Int:		return GL_INT;
			case Alpha::ElementType::Int2:		return GL_INT;
			case Alpha::ElementType::Int3:		return GL_INT;
			case Alpha::ElementType::Int4:		return GL_INT;
			case Alpha::ElementType::UInt:		return GL_UNSIGNED_INT;
			case Alpha::ElementType::UInt2:		return GL_UNSIGNED_INT;
			case Alpha::ElementType::UInt3:		return GL_UNSIGNED_INT;
			case Alpha::ElementType::UInt4:		return GL_UNSIGNED_INT;
			case Alpha::ElementType::Float:		return GL_FLOAT;
			case Alpha::ElementType::Float2:	return GL_FLOAT;
			case Alpha::ElementType::Float3:	return GL_FLOAT;
			case Alpha::ElementType::Float4:	return GL_FLOAT;
			case Alpha::ElementType::Double:	return GL_DOUBLE;
			case Alpha::ElementType::Double2:	return GL_DOUBLE;
			case Alpha::ElementType::Double3:	return GL_DOUBLE;
			case Alpha::ElementType::Double4:	return GL_DOUBLE;
		}

		return 0U;
	}

	const char* BufferElement::BaseTypeName(ElementType type)
	{
		switch (type)
		{
			case Alpha::ElementType::Int:		return "GL_INT";
			case Alpha::ElementType::Int2:		return "GL_INT";
			case Alpha::ElementType::Int3:		return "GL_INT";
			case Alpha::ElementType::Int4:		return "GL_INT";
			case Alpha::ElementType::UInt:		return "GL_UNSIGNED_INT";
			case Alpha::ElementType::UInt2:		return "GL_UNSIGNED_INT";
			case Alpha::ElementType::UInt3:		return "GL_UNSIGNED_INT";
			case Alpha::ElementType::UInt4:		return "GL_UNSIGNED_INT";
			case Alpha::ElementType::Float:		return "GL_FLOAT";
			case Alpha::ElementType::Float2:	return "GL_FLOAT";
			case Alpha::ElementType::Float3:	return "GL_FLOAT";
			case Alpha::ElementType::Float4:	return "GL_FLOAT";
			case Alpha::ElementType::Double:	return "GL_DOUBLE";
			case Alpha::ElementType::Double2:	return "GL_DOUBLE";
			case Alpha::ElementType::Double3:	return "GL_DOUBLE";
			case Alpha::ElementType::Double4:	return "GL_DOUBLE";
		}
		return nullptr;
	}


	////////////////////////
	// Buffer Layout ///////
	////////////////////////

	BufferLayout::BufferLayout() : m_Stride(0) {}

	BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements) :
		m_Elements(elements), m_Stride(0)
	{
		CalcStrideAndOffset();
	}

	std::ostream& operator<<(std::ostream& os, const BufferLayout& l)
	{
		uint16_t index = 0;
		for (const BufferElement& e : l.m_Elements)
		{
			os << "(Component : " << e.GetComponentCount() << ", ";
			os << "Type : " << e.GetTypeName() << ", ";
			os << "Stride : " << l.m_Stride << ", ";
			os << "Offset : " << e.Offset << ((index == l.m_Elements.size() - 1) ? ")" : ")\n");
			index++;
		}
		return os;
	}
}