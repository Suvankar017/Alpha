#include "pch.h"
#include "Alpha/OpenGL/OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Alpha
{
	/////////////////////////
	// Vertex Buffer ////////
	/////////////////////////

	VertexArray* VertexArray::Create()
	{
		return new OpenGLVertexArray();
	}

	VertexArrayScope VertexArray::CreateScope()
	{
		return std::make_unique<OpenGLVertexArray>();
	}

	VertexArrayRef VertexArray::CreateRef()
	{
		return std::make_shared<OpenGLVertexArray>();
	}

	void VertexArray::Destroy(VertexArray*& array)
	{
		if (array == nullptr) return;
		delete array;
		array = nullptr;
	}

	
	////////////////////////////////
	// OpenGL Vertex Buffer ////////
	////////////////////////////////

	OpenGLVertexArray::OpenGLVertexArray()
	{
		m_VertexCount = 0;
		m_IndexCount = 0;
		glGenVertexArrays(1, &m_ArrayID);

		AP_INFO("Generated VAO (ID : {})", m_ArrayID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_ArrayID);

		AP_INFO("Deleted VAO (ID : {})", m_ArrayID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_ArrayID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVBO(const VertexBufferRef& buffer)
	{
		if (buffer->GetLayout().GetElements().size() == 0)
		{
			AP_ERROR("Unable to add {} to {}, BufferLayout not found", *buffer, *this);
			return;
		}

		glBindVertexArray(m_ArrayID);
		buffer->Bind();

		const BufferLayout& layout = buffer->GetLayout();
		for (const BufferElement& e : layout)
		{
			AP_TRACE("Attrib : (Index : {}, Component : {}, BaseType : {}, IsNormalized : {}, Stride : {}, Offset : {})",
				m_VertexCount,
				e.GetComponentCount(),
				BufferElement::BaseTypeName(e.Type),
				e.IsNormalized ? "True" : "False",
				layout.GetStride(),
				e.Offset);

			glVertexAttribPointer(m_VertexCount,
				e.GetComponentCount(),
				e.ToBaseType(),
				e.IsNormalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)(size_t)e.Offset);

			glEnableVertexAttribArray(m_VertexCount);
			m_VertexCount++;
		}

		glBindVertexArray(0);
		buffer->Unbind();

		m_VBOs.push_back(buffer);

		AP_INFO("Binded {} to {}, VertexCount : {}", *buffer, *this, m_VertexCount);
	}

	void OpenGLVertexArray::SetIBO(const IndexBufferRef& buffer)
	{
		glBindVertexArray(m_ArrayID);
		buffer->Bind();

		glBindVertexArray(0);
		buffer->Unbind();

		m_IBO = buffer;
		m_IndexCount = m_IBO ? m_IBO->GetCount() : 0U;

		AP_INFO("Binded {} to {}", *buffer, *this);
	}

	std::ostream& OpenGLVertexArray::ToOutStream(std::ostream& os, const VertexArray& vao) const
	{
		const auto& array = (OpenGLVertexArray&)vao;
		return os << "VAO (ID : " << array.m_ArrayID << ")";
	}
}