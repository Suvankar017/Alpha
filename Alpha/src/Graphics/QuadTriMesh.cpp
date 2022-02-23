#include "pch.h"
#include "Alpha/Graphics/QuadTriMesh.h"

#include <glad/glad.h>

namespace Alpha
{
	QuadTriMesh::QuadTriMesh(const QuadTriProps& props)
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VerticesVBO);
		glGenBuffers(1, &m_ColorsVBO);
		glGenBuffers(1, &m_IBO);

		const auto& vertices = props.Vertices;
		const auto& colors = props.Colors;
		const auto& triangles = props.Triangles;

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VerticesVBO);
		glBufferData(GL_ARRAY_BUFFER, 100U * sizeof(glm::vec3), &vertices[0].x, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, m_ColorsVBO);
		glBufferData(GL_ARRAY_BUFFER, 100U * sizeof(glm::vec4), &colors[0].r, GL_DYNAMIC_DRAW);
		
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 100U * sizeof(uint32_t), triangles.data(), GL_DYNAMIC_DRAW);

		glBindVertexArray(0);

		m_IndexCount = (uint32_t)triangles.size();

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	QuadTriMesh::~QuadTriMesh()
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VerticesVBO);
		glDeleteBuffers(1, &m_ColorsVBO);
		glDeleteBuffers(1, &m_IBO);
	}

	void QuadTriMesh::Draw() const
	{
		glClearColor(0.33f, 0.541f, 0.167f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
	}

	void QuadTriMesh::SetData(const QuadTriProps& props)
	{
		const auto& vertices = props.Vertices;
		const auto& colors = props.Colors;
		const auto& triangles = props.Triangles;

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VerticesVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0U, vertices.size() * sizeof(glm::vec3), &vertices[0].x);

		glBindBuffer(GL_ARRAY_BUFFER, m_ColorsVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0U, colors.size() * sizeof(glm::vec4), &colors[0].r);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0U, triangles.size() * sizeof(uint32_t), triangles.data());

		glBindVertexArray(0);

		m_IndexCount = (uint32_t)triangles.size();
	}
}