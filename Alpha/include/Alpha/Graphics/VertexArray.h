#pragma once

#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "Alpha/Graphics/Buffer.h"

namespace Alpha
{
	////////////////////////
	// Vertex Array ////////
	////////////////////////

	class VertexArray;
	DEF_SMART_POINTER(VertexArray);

	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const std::vector<VertexBufferRef>& GetVBOs() const = 0;
		virtual const IndexBufferRef& GetIBO() const = 0;
		virtual uint32_t GetVertexCount() const = 0;
		virtual uint32_t GetIndexCount() const = 0;

		virtual void AddVBO(const VertexBufferRef& buffer) = 0;
		virtual void SetIBO(const IndexBufferRef& buffer) = 0;

		friend std::ostream& operator<<(std::ostream& os, const VertexArray& vao) { return vao.ToOutStream(os, vao); }

		static VertexArray* Create();
		static VertexArrayScope CreateScope();
		static VertexArrayRef CreateRef();
		static void Destroy(VertexArray*& array);

	protected:
		virtual std::ostream& ToOutStream(std::ostream& os, const VertexArray& vao) const { return os << "Base-VAO"; }
	};
}

#endif // !VERTEXARRAY_H
