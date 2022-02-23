#include "pch.h"
#include "Alpha/Graphics/Shader.h"

#include <glad/glad.h>

namespace Alpha
{
	ShaderRef Shader::CreateRef(const ShaderSource& srcs)
	{
		ShaderRef shader(new Shader(srcs));
		return shader;
	}

	Shader::Shader(const ShaderSource& srcs)
	{
		uint32_t vertex = CompileShader(GL_VERTEX_SHADER, srcs.VertexSrc);
		uint32_t geometry = CompileShader(GL_GEOMETRY_SHADER, srcs.GeometrySrc);
		uint32_t fragment = CompileShader(GL_FRAGMENT_SHADER, srcs.FragmentSrc);

		m_ShaderID = LinkProgram(vertex, geometry, fragment);

		glDeleteShader(vertex);
		glDeleteShader(geometry);
		glDeleteShader(fragment);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_ShaderID);
		AP_INFO("Shader : {} deleted", m_ShaderID);
	}

	int Shader::GetUniformID(const std::string& uniformName)
	{
		int id = -1;
		auto it = m_UniformLocations.find(uniformName);

		if (it == m_UniformLocations.end())
		{
			id = glGetUniformLocation(m_ShaderID, uniformName.c_str());
			if (id > -1) m_UniformLocations[uniformName] = id;
			return id;
		}

		return it->second;
	}

	void Shader::SetUniform(int uniformID, int value)
	{
		glUseProgram(m_ShaderID);
		glUniform1i(uniformID, value);
	}

	void Shader::SetUniform(int uniformID, float value)
	{
		glUseProgram(m_ShaderID);
		glUniform1f(uniformID, value);
	}

	void Shader::SetUniform(int uniformID, const glm::vec2& value)
	{
		glUseProgram(m_ShaderID);
		glUniform2f(uniformID, value.x, value.y);
	}

	void Shader::SetUniform(int uniformID, const glm::vec3& value)
	{
		glUseProgram(m_ShaderID);
		glUniform3f(uniformID, value.x, value.y, value.z);
	}

	void Shader::SetUniform(int uniformID, const glm::vec4& value)
	{
		glUseProgram(m_ShaderID);
		glUniform4f(uniformID, value.x, value.y, value.z, value.w);
	}

	void Shader::SetUniform(int uniformID, const glm::mat3& value)
	{
		glUseProgram(m_ShaderID);
		glUniformMatrix3fv(uniformID, 1, GL_FALSE, &value[0][0]);
	}

	void Shader::SetUniform(int uniformID, const glm::mat4& value)
	{
		glUseProgram(m_ShaderID);
		glUniformMatrix4fv(uniformID, 1, GL_FALSE, &value[0][0]);
	}

	void Shader::SetUniform(const std::string& uniformName, int value)
	{
		glUseProgram(m_ShaderID);
		glUniform1i(GetUniformID(uniformName), value);
	}

	void Shader::SetUniform(const std::string& uniformName, float value)
	{
		glUseProgram(m_ShaderID);
		glUniform1f(GetUniformID(uniformName), value);
	}

	void Shader::SetUniform(const std::string& uniformName, const glm::vec2& value)
	{
		glUseProgram(m_ShaderID);
		glUniform2f(GetUniformID(uniformName), value.x, value.y);
	}

	void Shader::SetUniform(const std::string& uniformName, const glm::vec3& value)
	{
		glUseProgram(m_ShaderID);
		glUniform3f(GetUniformID(uniformName), value.x, value.y, value.z);
	}

	void Shader::SetUniform(const std::string& uniformName, const glm::vec4& value)
	{
		glUseProgram(m_ShaderID);
		glUniform4f(GetUniformID(uniformName), value.x, value.y, value.z, value.w);
	}

	void Shader::SetUniform(const std::string& uniformName, const glm::mat3& value)
	{
		glUseProgram(m_ShaderID);
		glUniformMatrix3fv(GetUniformID(uniformName), 1, GL_FALSE, &value[0][0]);
	}

	void Shader::SetUniform(const std::string& uniformName, const glm::mat4& value)
	{
		glUseProgram(m_ShaderID);
		glUniformMatrix4fv(GetUniformID(uniformName), 1, GL_FALSE, &value[0][0]);
	}

	const char* Shader::GetTypeName(uint32_t type)
	{
		switch (type)
		{
			case GL_VERTEX_SHADER:		 return "Vertex";
			case GL_GEOMETRY_SHADER:	 return "Geometry";
			case GL_FRAGMENT_SHADER:	 return "Fragment";
		}
		return nullptr;
	}

	uint32_t Shader::CompileShader(uint32_t type, const std::string& src)
	{
		if (src.empty()) return 0u;

		uint32_t shaderID;
		const uint32_t maxSize = 512u;
		const char* shaderSrc = src.c_str();
		char errorLog[maxSize];
		int success;

		shaderID = glCreateShader(type);
		glShaderSource(shaderID, 1, &shaderSrc, nullptr);
		glCompileShader(shaderID);

		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shaderID, maxSize, nullptr, errorLog);
			AP_ERROR("Compilation Failed : {} Shader\n{}\n{}", GetTypeName(type), errorLog, src);
			glDeleteShader(shaderID);
			shaderID = 0u;
		}

		return shaderID;
	}

	uint32_t Shader::LinkProgram(uint32_t vertexShader, uint32_t geometryShader, uint32_t fragmentShader)
	{
		uint32_t programID;
		const uint32_t maxSize = 512u;
		char errorLog[maxSize];
		int success;

		programID = glCreateProgram();
		if (vertexShader) glAttachShader(programID, vertexShader);
		if (geometryShader) glAttachShader(programID, geometryShader);
		if (fragmentShader) glAttachShader(programID, fragmentShader);
		glLinkProgram(programID);

		glGetProgramiv(programID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(programID, maxSize, nullptr, errorLog);
			AP_ERROR("Linking Failed : Shader Program\n{}", errorLog);
		}

		return programID;
	}
}