#include "pch.h"
#include "Alpha/Graphics/RenderCommand.h"

#include <glad/glad.h>

namespace Alpha
{
	RenderMeshCommand::RenderMeshCommand(const MeshTemp& mesh, const ShaderTemp& shader) :
		m_Mesh(mesh), m_Shader(shader)
	{

	}

	RenderMeshCommand::~RenderMeshCommand()
	{

	}

	void RenderMeshCommand::Execute() const
	{
		MeshRef mesh = m_Mesh.lock();
		ShaderRef shader = m_Shader.lock();

		if (!mesh || !shader)
		{
			return;
		}

		glUseProgram(shader->GetID());
		glBindVertexArray(mesh->GetVAO());
		glDrawElements(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
		glUseProgram(0);
	}


	RenderMeshTextureCommand::RenderMeshTextureCommand(const MeshTemp& mesh, const ShaderTemp& shader, const Texture2DTemp& texture) :
		m_Mesh(mesh), m_Shader(shader), m_Texture(texture)
	{

	}

	RenderMeshTextureCommand::~RenderMeshTextureCommand()
	{

	}

	void RenderMeshTextureCommand::Execute() const
	{
		MeshRef mesh = m_Mesh.lock();
		ShaderRef shader = m_Shader.lock();
		Texture2DRef texture = m_Texture.lock();

		if (!mesh || !shader || !texture)
		{
			return;
		}

		glUseProgram(shader->GetID());

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->GetID());

		glBindVertexArray(mesh->GetVAO());
		glDrawElements(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);

		glUseProgram(0);
	}


	RenderMeshMaterialCommand::RenderMeshMaterialCommand(const MeshTemp& mesh, const MaterialTemp& material) :
		m_Mesh(mesh), m_Material(material)
	{

	}

	RenderMeshMaterialCommand::~RenderMeshMaterialCommand()
	{

	}

	void RenderMeshMaterialCommand::Execute() const
	{
		MeshRef mesh = m_Mesh.lock();
		MaterialRef material = m_Material.lock();

		if (!mesh || !material)
		{
			return;
		}

		const ShaderRef shader = material->GetShader();

		glUseProgram(shader->GetID());

		int slot = 0;
		for (const auto& it : material->GetTextures())
		{
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, it.second->GetID());
			shader->SetUniform(it.first, slot);
			slot++;
		}

		for (const auto& it : material->GetInts())
		{
			shader->SetUniform(it.first, it.second);
		}
		for (const auto& it : material->GetFloats())
		{
			shader->SetUniform(it.first, it.second);
		}
		for (const auto& it : material->GetVec2s())
		{
			shader->SetUniform(it.first, it.second);
		}
		for (const auto& it : material->GetVec3s())
		{
			shader->SetUniform(it.first, it.second);
		}
		for (const auto& it : material->GetVec4s())
		{
			shader->SetUniform(it.first, it.second);
		}
		for (const auto& it : material->GetMat3s())
		{
			shader->SetUniform(it.first, it.second);
		}
		for (const auto& it : material->GetMat4s())
		{
			shader->SetUniform(it.first, it.second);
		}

		glBindVertexArray(mesh->GetVAO());
		glDrawElements(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);

		glUseProgram(0);
	}
}