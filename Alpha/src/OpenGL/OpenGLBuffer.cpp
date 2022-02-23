#include "pch.h"
#include "Alpha/OpenGL/OpenGLBuffer.h"

#include <glad/glad.h>

namespace Alpha
{
	////////////////////////
	// Vertex Buffer ///////
	////////////////////////

	VertexBuffer* VertexBuffer::Create(size_t size, const void* data, BufferType bufferType)
	{
		return new OpenGLVertexBuffer(size, data, bufferType);
	}

	VertexBufferScope VertexBuffer::CreateScope(size_t size, const void* data, BufferType bufferType)
	{
		return std::make_unique<OpenGLVertexBuffer>(size, data, bufferType);
	}

	VertexBufferRef VertexBuffer::CreateRef(size_t size, const void* data, BufferType bufferType)
	{
		return std::make_shared<OpenGLVertexBuffer>(size, data, bufferType);
	}

	void VertexBuffer::Destroy(VertexBuffer*& buffer)
	{
		if (buffer == nullptr) return;
		delete buffer;
		buffer = nullptr;
	}


	////////////////////////////////
	// OpenGL Vertex Buffer ////////
	////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(size_t size, const void* data, BufferType bufferType) :
		m_BufferType(bufferType)
	{
		glGenBuffers(1, &m_BufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ARRAY_BUFFER, size, data, (uint32_t)bufferType);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		AP_INFO("Generated VBO (ID : {}, Type : {})", m_BufferID, BufferTypeToString(bufferType));
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_BufferID);
		AP_INFO("Deleted VBO (ID : {}, Type : {})", m_BufferID, BufferTypeToString(m_BufferType));
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetData(uint32_t offset, size_t size, const void* data)
	{
		if (m_BufferType != BufferType::Dynamic) return;
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	}

	std::ostream& OpenGLVertexBuffer::ToOutStream(std::ostream& os, const VertexBuffer& vbo) const
	{
		const auto& buffer = (OpenGLVertexBuffer&)vbo;
		return os << "VBO (ID : " << buffer.m_BufferID << ")";
	}


	////////////////////////
	// Index Buffer ////////
	////////////////////////

	IndexBuffer* IndexBuffer::Create(size_t size, const uint32_t* data, uint32_t count, BufferType type)
	{
		return new OpenGLIndexBuffer(size, data, count, type);
	}

	IndexBufferScope IndexBuffer::CreateScope(size_t size, const uint32_t* data, uint32_t count, BufferType type)
	{
		return std::make_unique<OpenGLIndexBuffer>(size, data, count, type);
	}

	IndexBufferRef IndexBuffer::CreateRef(size_t size, const uint32_t* data, uint32_t count, BufferType type)
	{
		return std::make_shared<OpenGLIndexBuffer>(size, data, count, type);
	}

	void IndexBuffer::Destroy(IndexBuffer*& buffer)
	{
		if (buffer == nullptr) return;
		delete buffer;
		buffer = nullptr;
	}


	///////////////////////////////
	// OpenGL Index Buffer ////////
	///////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(size_t size, const uint32_t* data, uint32_t count, BufferType bufferType) :
		m_BufferType(bufferType)
	{
		glGenBuffers(1, &m_BufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, (uint32_t)bufferType);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		if (bufferType == BufferType::Dynamic)
			m_Count = count;
		else
			m_Count = (data == nullptr) ? 0U : (uint32_t)(size / sizeof(uint32_t));

		AP_INFO("Generated IBO (ID : {}, Type : {})", m_BufferID, BufferTypeToString(bufferType));
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_BufferID);
		AP_INFO("Deleted IBO (ID : {}, Type : {})", m_BufferID, BufferTypeToString(m_BufferType));
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void OpenGLIndexBuffer::SetData(uint32_t offset, size_t size, const uint32_t* data)
	{
		if (m_BufferType != BufferType::Dynamic) return;

		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
		m_Count = (uint32_t)(offset + size) / sizeof(uint32_t);
	}

	std::ostream& OpenGLIndexBuffer::ToOutStream(std::ostream& os, const IndexBuffer& ibo) const
	{
		const auto& buffer = (OpenGLIndexBuffer&)ibo;
		return os << "IBO (ID : " << buffer.m_BufferID << ")";
	}
}
