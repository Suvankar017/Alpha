#include "pch.h"
#include "Alpha/Graphics/Mesh.h"

#include <glad/glad.h>

#define MAX_VERTEX_COUNT 100U

#define MAX_VERTICES_SIZE MAX_VERTEX_COUNT * sizeof(glm::vec3)
#define MAX_COLORS_SIZE MAX_VERTEX_COUNT * sizeof(glm::vec4)
#define MAX_UVS_SIZE MAX_VERTEX_COUNT * sizeof(glm::vec2)
#define MAX_INDICES_SIZE MAX_VERTEX_COUNT * sizeof(uint32_t)

namespace Alpha
{
	Mesh::Mesh() : m_IsStatic(false)
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VerticesVBO);
		glGenBuffers(1, &m_ColorsVBO);
		glGenBuffers(1, &m_UVsVBO);
		glGenBuffers(1, &m_IBO);


		glBindVertexArray(m_VAO);

		// Vertices
		glBindBuffer(GL_ARRAY_BUFFER, m_VerticesVBO);
		glBufferData(GL_ARRAY_BUFFER, MAX_VERTICES_SIZE, nullptr, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
		glEnableVertexAttribArray(0);

		// Colors
		glBindBuffer(GL_ARRAY_BUFFER, m_ColorsVBO);
		glBufferData(GL_ARRAY_BUFFER, MAX_COLORS_SIZE, nullptr, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
		glEnableVertexAttribArray(1);

		// UVs
		glBindBuffer(GL_ARRAY_BUFFER, m_UVsVBO);
		glBufferData(GL_ARRAY_BUFFER, MAX_UVS_SIZE, nullptr, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
		glEnableVertexAttribArray(2);

		// Triangles
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_INDICES_SIZE, nullptr, GL_DYNAMIC_DRAW);

		glBindVertexArray(0);

		m_IndexCount = 0u;
	}

	Mesh::Mesh(const MeshProps& props, bool isStatic) : m_IsStatic(isStatic)
	{
		m_Vertices = props.Vertices;
		m_Colors = props.Colors;
		m_UVs = props.UVs;
		m_Triangles = props.Triangles;

		const float* vertices = (m_Vertices.data() == nullptr) ? nullptr : &m_Vertices[0].x;
		const float* colors = (m_Colors.data() == nullptr) ? nullptr : &m_Colors[0].r;
		const float* uvs = (m_UVs.data() == nullptr) ? nullptr : &m_UVs[0].x;

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VerticesVBO);
		glGenBuffers(1, &m_ColorsVBO);
		glGenBuffers(1, &m_UVsVBO);
		glGenBuffers(1, &m_IBO);

		glBindVertexArray(m_VAO);

		if (isStatic)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VerticesVBO);
			glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(glm::vec3), vertices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
			glEnableVertexAttribArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, m_ColorsVBO);
			glBufferData(GL_ARRAY_BUFFER, m_Colors.size() * sizeof(glm::vec4), colors, GL_STATIC_DRAW);

			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
			glEnableVertexAttribArray(1);

			glBindBuffer(GL_ARRAY_BUFFER, m_UVsVBO);
			glBufferData(GL_ARRAY_BUFFER, m_UVs.size() * sizeof(glm::vec2), uvs, GL_STATIC_DRAW);

			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
			glEnableVertexAttribArray(2);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Triangles.size() * sizeof(uint32_t), m_Triangles.data(), GL_STATIC_DRAW);
		}
		else
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VerticesVBO);
			glBufferData(GL_ARRAY_BUFFER, MAX_VERTICES_SIZE, vertices, GL_DYNAMIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
			glEnableVertexAttribArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, m_ColorsVBO);
			glBufferData(GL_ARRAY_BUFFER, MAX_COLORS_SIZE, colors, GL_DYNAMIC_DRAW);

			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
			glEnableVertexAttribArray(1);

			glBindBuffer(GL_ARRAY_BUFFER, m_UVsVBO);
			glBufferData(GL_ARRAY_BUFFER, MAX_UVS_SIZE, uvs, GL_DYNAMIC_DRAW);

			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
			glEnableVertexAttribArray(2);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_INDICES_SIZE, m_Triangles.data(), GL_DYNAMIC_DRAW);
		}

		glBindVertexArray(0);

		m_IndexCount = (uint32_t)m_Triangles.size();
	}

	Mesh::~Mesh()
	{
		m_Vertices.clear();
		m_Colors.clear();
		m_UVs.clear();
		m_Triangles.clear();

		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VerticesVBO);
		glDeleteBuffers(1, &m_ColorsVBO);
		glDeleteBuffers(1, &m_UVsVBO);
		glDeleteBuffers(1, &m_IBO);
	}

	void Mesh::SetVertices(const std::vector<glm::vec3>& vertices)
	{
		if (m_IsStatic) return;

		const float* data = (vertices.data() == nullptr) ? nullptr : &vertices[0].x;
		
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VerticesVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0u, vertices.size() * sizeof(glm::vec3), data);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		m_Vertices = vertices;

		AP_TRACE("Vertices size : {} bytes", vertices.size() * sizeof(glm::vec3));
	}

	void Mesh::SetColors(const std::vector<glm::vec4>& colors)
	{
		if (m_IsStatic) return;

		const float* data = (colors.data() == nullptr) ? nullptr : &colors[0].r;

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_ColorsVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0u, colors.size() * sizeof(glm::vec4), data);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		m_Colors = colors;

		AP_TRACE("Colors size : {} bytes", colors.size() * sizeof(glm::vec3));
	}

	void Mesh::SetUVs(const std::vector<glm::vec2>& uvs)
	{
		if (m_IsStatic) return;

		const float* data = (uvs.data() == nullptr) ? nullptr : &uvs[0].x;

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_UVsVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0u, uvs.size() * sizeof(glm::vec2), data);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		m_UVs = uvs;

		AP_TRACE("UVs size : {} bytes", uvs.size() * sizeof(glm::vec2));
	}

	void Mesh::SetTriangles(const std::vector<uint32_t>& triangles)
	{
		if (m_IsStatic) return;

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0u, triangles.size() * sizeof(uint32_t), triangles.data());
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		
		m_IndexCount = (uint32_t)triangles.size();
		m_Triangles = triangles;
	}

	MeshRef Mesh::CreateRef()
	{
		MeshRef mesh(new Mesh());
		return mesh;
	}

	MeshRef Mesh::CreateRef(const MeshProps& props, bool isStatic)
	{
		MeshRef mesh(new Mesh(props, isStatic));
		return mesh;
	}
}