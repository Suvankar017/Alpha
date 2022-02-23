#pragma once

#ifndef OPENGLBUFFER_H
#define OPENGLBUFFER_H

#include "Alpha/Graphics/Buffer.h"

namespace Alpha
{
	////////////////////////////////
	// OpenGL Vertex Buffer ////////
	////////////////////////////////

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(size_t size, const void* data, BufferType bufferType);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetData(uint32_t offset, size_t size, const void* data) override;

		inline virtual BufferType GetBufferType() const override { return m_BufferType; }
		inline virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		inline virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

	protected:
		virtual std::ostream& ToOutStream(std::ostream& os, const VertexBuffer& vbo) const override;
	
	private:
		BufferLayout m_Layout;
		uint32_t m_BufferID;
		BufferType m_BufferType;
	};


	///////////////////////////////
	// OpenGL Index Buffer ////////
	///////////////////////////////

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(size_t size, const uint32_t* data, uint32_t count, BufferType type);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetData(uint32_t offset, size_t size, const uint32_t* data) override;

		inline virtual BufferType GetBufferType() const override { return m_BufferType; }
		inline virtual uint32_t GetCount() const override { return m_Count; }

	protected:
		virtual std::ostream& ToOutStream(std::ostream& os, const IndexBuffer& ibo) const override;

	private:
		uint32_t m_BufferID;
		uint32_t m_Count;
		BufferType m_BufferType;
	};
}

#endif // !OPENGLBUFFER_H
