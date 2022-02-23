#pragma once

#include <stdint.h>
#include <vector>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace Alpha
{
	struct QuadTriProps
	{
		std::vector<glm::vec3> Vertices;
		std::vector<glm::vec4> Colors;
		std::vector<uint32_t> Triangles;
	};

	class QuadTriMesh
	{
	public:
		QuadTriMesh(const QuadTriProps& props);
		~QuadTriMesh();

		void Draw() const;

		void SetData(const QuadTriProps& props);

	private:
		uint32_t m_VAO;
		uint32_t m_VerticesVBO;
		uint32_t m_ColorsVBO;
		uint32_t m_IBO;
		uint32_t m_IndexCount;
	};
}