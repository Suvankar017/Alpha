#pragma once

#include <string>
#include <unordered_map>
#include <type_traits>

#include <glm/glm.hpp>

#include "Alpha/Macros.h"
#include "Alpha/Graphics/Shader.h"
#include "Alpha/Graphics/Texture.h"

namespace Alpha
{
	class Material;
	DEF_SMART_POINTER(Material);

	class Material
	{
	public:
		~Material();

		inline const ShaderRef& GetShader() const { return m_Shader; }
		inline const std::unordered_map<std::string, int>& GetInts() const { return m_UniformInts; }
		inline const std::unordered_map<std::string, float> & GetFloats() const { return m_UniformFloats; }
		inline const std::unordered_map<std::string, glm::vec2>& GetVec2s() const { return m_UniformVec2s; }
		inline const std::unordered_map<std::string, glm::vec3>& GetVec3s() const { return m_UniformVec3s; }
		inline const std::unordered_map<std::string, glm::vec4>& GetVec4s() const { return m_UniformVec4s; }
		inline const std::unordered_map<std::string, glm::mat3>& GetMat3s() const { return m_UniformMat3s; }
		inline const std::unordered_map<std::string, glm::mat4>& GetMat4s() const { return m_UniformMat4s; }
		inline const std::unordered_map<std::string, Texture2DRef>& GetTextures() const { return m_UniformTextures; }

		void SetShader(const ShaderRef& shader);
		
#define GET_VALUE(map, defaultReturn) const auto& it = map.find(name);\
		return (it == map.end()) ? defaultReturn : it->second;

		template<typename T>
		inline T GetValue(const std::string& name) const
		{
			if constexpr (std::is_same<T, int>())			 { GET_VALUE(m_UniformInts, 0); }
			if constexpr (std::is_same<T, float>())			 { GET_VALUE(m_UniformFloats, 0.0f); }
			if constexpr (std::is_same<T, glm::vec2>())		 { GET_VALUE(m_UniformVec2s, glm::vec2(0.0f)); }
			if constexpr (std::is_same<T, glm::vec3>())		 { GET_VALUE(m_UniformVec3s, glm::vec3(0.0f)); }
			if constexpr (std::is_same<T, glm::vec4>())		 { GET_VALUE(m_UniformVec4s, glm::vec4(0.0f)); }
			if constexpr (std::is_same<T, glm::mat3>())		 { GET_VALUE(m_UniformMat3s, glm::mat3(1.0f)); }
			if constexpr (std::is_same<T, glm::mat4>())		 { GET_VALUE(m_UniformMat4s, glm::mat4(1.0f)); }
			if constexpr (std::is_same<T, Texture2DRef>())	 { GET_VALUE(m_UniformTextures, nullptr); }
		}

#undef GET_VALUE

		template<typename T>
		inline void SetValue(const std::string& name, const T& value)
		{
			if constexpr (std::is_same<T, int>())			 { m_UniformInts[name] = value; }
			if constexpr (std::is_same<T, float>())			 { m_UniformFloats[name] = value; }
			if constexpr (std::is_same<T, glm::vec2>())		 { m_UniformVec2s[name] = value; }
			if constexpr (std::is_same<T, glm::vec3>())		 { m_UniformVec3s[name] = value; }
			if constexpr (std::is_same<T, glm::vec4>())		 { m_UniformVec4s[name] = value; }
			if constexpr (std::is_same<T, glm::mat3>())		 { m_UniformMat3s[name] = value; }
			if constexpr (std::is_same<T, glm::mat4>())		 { m_UniformMat4s[name] = value; }
			if constexpr (std::is_same<T, Texture2DRef>())	 { m_UniformTextures[name] = value; }
		}

		static MaterialRef CreateRef(const ShaderRef& shader);

	private:
		Material(const ShaderRef& shader);

	private:
		ShaderRef m_Shader;

		std::unordered_map<std::string, int> m_UniformInts;
		std::unordered_map<std::string, float> m_UniformFloats;
		std::unordered_map<std::string, glm::vec2> m_UniformVec2s;
		std::unordered_map<std::string, glm::vec3> m_UniformVec3s;
		std::unordered_map<std::string, glm::vec4> m_UniformVec4s;
		std::unordered_map<std::string, glm::mat3> m_UniformMat3s;
		std::unordered_map<std::string, glm::mat4> m_UniformMat4s;
		std::unordered_map<std::string, Texture2DRef> m_UniformTextures;
	};
}
