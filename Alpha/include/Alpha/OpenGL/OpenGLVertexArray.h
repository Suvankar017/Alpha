#pragma once

#ifndef OPENGLVERTEXARRAY_H
#define OPENGLVERTEXARRAY_H

#include "Alpha/Graphics/VertexArray.h"

namespace Alpha
{
	////////////////////////////////
	// OpenGL Vertex Buffer ////////
	////////////////////////////////

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		inline virtual const std::vector<VertexBufferRef>& GetVBOs() const override { return m_VBOs; }
		inline virtual const IndexBufferRef& GetIBO() const override { return m_IBO; }
		inline virtual uint32_t GetVertexCount() const override { return m_VertexCount; }
		inline virtual uint32_t GetIndexCount() const override { return m_IndexCount; }

		virtual void AddVBO(const VertexBufferRef& buffer) override;
		virtual void SetIBO(const IndexBufferRef& buffer) override;

	protected:
		virtual std::ostream& ToOutStream(std::ostream& os, const VertexArray& vao) const override;

	private:
		uint32_t m_ArrayID;
		uint32_t m_VertexCount;
		uint32_t m_IndexCount;
		std::vector<VertexBufferRef> m_VBOs;
		IndexBufferRef m_IBO;
	};
}

#endif // !OPENGLVERTEXARRAY_H
