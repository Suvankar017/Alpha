#pragma once

#include "Alpha/Macros.h"
#include "Alpha/Graphics/Mesh.h"
#include "Alpha/Graphics/Shader.h"
#include "Alpha/Graphics/Texture.h"
#include "Alpha/Graphics/Material.h"

namespace Alpha
{
	class RenderCommand
	{
	public:
		virtual ~RenderCommand() {}
		virtual void Execute() const = 0;
	};

	DEF_SMART_POINTER(RenderCommand);


	class RenderMeshCommand : public RenderCommand
	{
	public:
		RenderMeshCommand(const MeshTemp& mesh, const ShaderTemp& shader);
		virtual ~RenderMeshCommand();
		virtual void Execute() const override;

	private:
		MeshTemp m_Mesh;
		ShaderTemp m_Shader;
	};

	DEF_SMART_POINTER(RenderMeshCommand);


	class RenderMeshTextureCommand : public RenderCommand
	{
	public:
		RenderMeshTextureCommand(const MeshTemp& mesh, const ShaderTemp& shader, const Texture2DTemp& texture);
		virtual ~RenderMeshTextureCommand();
		virtual void Execute() const override;

	private:
		MeshTemp m_Mesh;
		ShaderTemp m_Shader;
		Texture2DTemp m_Texture;
	};

	DEF_SMART_POINTER(RenderMeshTextureCommand);


	class RenderMeshMaterialCommand : public RenderCommand
	{
	public:
		RenderMeshMaterialCommand(const MeshTemp& mesh, const MaterialTemp& material);
		virtual ~RenderMeshMaterialCommand();
		virtual void Execute() const override;

	private:
		MeshTemp m_Mesh;
		MaterialTemp m_Material;
	};

	DEF_SMART_POINTER(RenderMeshMaterialCommand);
}