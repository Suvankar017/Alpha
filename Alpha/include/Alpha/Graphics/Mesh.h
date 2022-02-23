#pragma once

#ifndef MESH_H
#define MESH_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Alpha/Macros.h"

namespace Alpha
{
	struct MeshProps
	{
		std::vector<glm::vec3> Vertices;
		std::vector<glm::vec4> Colors;
		std::vector<glm::vec2> UVs;
		std::vector<uint32_t> Triangles;
	};

	class Mesh;

	DEF_SMART_POINTER(Mesh);

	class Mesh
	{
	public:
		~Mesh();

		void SetVertices(const std::vector<glm::vec3>& vertices);
		void SetColors(const std::vector<glm::vec4>& colors);
		void SetUVs(const std::vector<glm::vec2>& uvs);
		void SetTriangles(const std::vector<uint32_t>& triangles);

		inline const uint32_t GetVAO() const { return m_VAO; }
		inline const uint32_t GetVerticesVBO() const { return m_VerticesVBO; }
		inline const uint32_t GetColorsVBO() const { return m_ColorsVBO; }
		inline const uint32_t GetUVsVBO() const { return m_UVsVBO; }
		inline const uint32_t GetIBO() const { return m_IBO; }
		inline const uint32_t GetIndexCount() const { return m_IndexCount; }

		inline const std::vector<glm::vec3>& GetVertices() const { return m_Vertices; }
		inline const std::vector<glm::vec4>& GetColors() const { return m_Colors; }
		inline const std::vector<glm::vec2>& GetUVs() const { return m_UVs; }
		inline const std::vector<uint32_t>& GetTriangles() const { return m_Triangles; }
		inline bool IsStatic() const { return m_IsStatic; }

		static MeshRef CreateRef();
		static MeshRef CreateRef(const MeshProps& props, bool isStatic);

	private:
		uint32_t m_VAO;
		uint32_t m_VerticesVBO;
		uint32_t m_ColorsVBO;
		uint32_t m_UVsVBO;
		uint32_t m_IBO;
		uint32_t m_IndexCount;

		std::vector<glm::vec3> m_Vertices;
		std::vector<glm::vec4> m_Colors;
		std::vector<glm::vec2> m_UVs;
		std::vector<uint32_t> m_Triangles;
		bool m_IsStatic;

		Mesh();
		Mesh(const MeshProps& props, bool isStatic);
	};
}

#endif // !MESH_H
