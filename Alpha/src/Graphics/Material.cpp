#include "pch.h"
#include "Alpha/Graphics/Material.h"

namespace Alpha
{
	MaterialRef Material::CreateRef(const ShaderRef& shader)
	{
		MaterialRef material(new Material(shader));
		return material;
	}

	Material::Material(const ShaderRef& shader) :
		m_Shader(shader)
	{

	}

	Material::~Material()
	{

	}

	void Material::SetShader(const ShaderRef& shader)
	{
		m_Shader = shader;
	}
}