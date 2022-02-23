#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <stdint.h>
#include <string>
#include <unordered_map>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

#include "Alpha/Macros.h"

namespace Alpha
{
	struct ShaderSource
	{
		std::string VertexSrc;
		std::string GeometrySrc;
		std::string FragmentSrc;
	};

	class Shader;
	DEF_SMART_POINTER(Shader);

	class Shader
	{
	public:
		~Shader();

		inline uint32_t GetID() const { return m_ShaderID; }

		int GetUniformID(const std::string& uniformName);

		void SetUniform(int uniformID, int value);
		void SetUniform(int uniformID, float value);
		void SetUniform(int uniformID, const glm::vec2& value);
		void SetUniform(int uniformID, const glm::vec3& value);
		void SetUniform(int uniformID, const glm::vec4& value);
		void SetUniform(int uniformID, const glm::mat3& value);
		void SetUniform(int uniformID, const glm::mat4& value);

		void SetUniform(const std::string& uniformName, int value);
		void SetUniform(const std::string& uniformName, float value);
		void SetUniform(const std::string& uniformName, const glm::vec2& value);
		void SetUniform(const std::string& uniformName, const glm::vec3& value);
		void SetUniform(const std::string& uniformName, const glm::vec4& value);
		void SetUniform(const std::string& uniformName, const glm::mat3& value);
		void SetUniform(const std::string& uniformName, const glm::mat4& value);

		static ShaderRef CreateRef(const ShaderSource& srcs);

	private:
		Shader(const ShaderSource& srcs);

		static const char* GetTypeName(uint32_t type);
		static uint32_t CompileShader(uint32_t type, const std::string& src);
		static uint32_t LinkProgram(uint32_t vertexShader, uint32_t geometryShader, uint32_t fragmentShader);

	private:
		uint32_t m_ShaderID;
		std::unordered_map<std::string, int> m_UniformLocations;
	};
}

#endif // !SHADER_H
