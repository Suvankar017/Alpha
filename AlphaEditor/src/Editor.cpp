#include "Alpha/Core/App.h"
#include "Alpha/Debug/Log.h"

#include "Alpha/Core/Engine.h"
#include "Alpha/Input/Input.h"

#include "Alpha/Graphics/Mesh.h"
#include "Alpha/Graphics/Shader.h"
#include "Alpha/Graphics/Texture.h"
#include "Alpha/Graphics/Material.h"
#include "Alpha/Graphics/RenderCommand.h"
#include "Alpha/Graphics/Renderer.h"

#include <glm/glm.hpp>
#include <stb/stb_image.h>

class Editor : public Alpha::App
{
public:
	Editor()
	{
		std::string vertexShader = R"(
			#version 330 core
			layout (location = 0) in vec3 a_Pos;
			layout (location = 1) in vec4 a_Color;
			layout (location = 2) in vec2 a_UV;

			out vec4 Color;
			out vec2 UV;

			void main()
			{
				gl_Position = vec4(a_Pos, 1.0);
				Color = a_Color;
				UV = a_UV;
			}
		)";

		std::string fragmentShader = R"(
			#version 330 core
			in vec4 Color;
			in vec2 UV;

			uniform sampler2D wood;
			uniform sampler2D face;
			uniform vec2 tiling;

			out vec4 FragColor;
  
			void main()
			{
				FragColor = mix(texture(wood, UV * tiling), texture(face, UV * tiling), 0.5);
			}
		)";

		std::vector<glm::vec3> vertices =
		{
			{ 0.5f,  0.5f, 0.0f},
			{ 0.5f, -0.5f, 0.0f},
			{-0.5f, -0.5f, 0.0f},
			{-0.5f,  0.5f, 0.0f}
		};
		std::vector<glm::vec4> colors =
		{
			{1.0f, 1.0f, 0.0f, 1.0f},
			{1.0f, 0.0f, 0.0f, 1.0f},
			{0.0f, 0.0f, 0.0f, 1.0f},
			{0.0f, 1.0f, 0.0f, 1.0f}
		};
		std::vector<glm::vec2> uvs =
		{
			{1.0f, 1.0f},
			{1.0f, 0.0f},
			{0.0f, 0.0f},
			{0.0f, 1.0f}
		};
		std::vector<uint32_t> triangles =
		{
			0, 1, 2,
			2, 3, 0
		};

		// Load Textures
		{
			// Error
			float errorPixels[] =
			{
				1.0f, 0.0f, 1.0f,	 1.0f, 1.0f, 1.0f,
				1.0f, 1.0f, 1.0f,	 1.0f, 0.0f, 1.0f
			};

			// Wood
			{
				glm::ivec2 size;
				int channels;
				auto pixels = stbi_load("res/textures/Wood.jpg", &size.x, &size.y, &channels, 0);

				Alpha::TextureFormat format = (channels == 4) ? Alpha::TextureFormat::RGBA : Alpha::TextureFormat::RGB;
				m_WoodTex = Alpha::Texture2D::CreateRef(size, format, pixels);

				stbi_image_free(pixels);
			}
			// Face
			{
				glm::ivec2 size;
				int channels;
				auto pixels = stbi_load("res/textures/Face.png", &size.x, &size.y, &channels, 0);

				Alpha::TextureFormat format = (channels == 4) ? Alpha::TextureFormat::RGBA : Alpha::TextureFormat::RGB;
				m_FaceTex = Alpha::Texture2D::CreateRef(size, format, pixels);

				stbi_image_free(pixels);
			}
		}

		m_Shader = Alpha::Shader::CreateRef({ vertexShader, "", fragmentShader });

		m_Mat = Alpha::Material::CreateRef(m_Shader);
		m_Mat->SetValue("wood", m_WoodTex);
		m_Mat->SetValue("face", m_FaceTex);
		m_Mat->SetValue("tiling", glm::vec2(1.0f, 1.0f));

		m_Mesh = Alpha::Mesh::CreateRef({ vertices, colors, uvs, triangles }, true);

		m_Command = std::make_shared<Alpha::RenderMeshMaterialCommand>(m_Mesh, m_Mat);
	}

	virtual ~Editor()
	{

	}

	static glm::vec4 GetColor(int r, int g, int b, int a)
	{
		return { r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f };
	}

	virtual void OnUpdate() override
	{
		if (Alpha::Input::GetKeyDown(Alpha::KeyCode::Escape))
		{
			Close();
		}

		if (Alpha::Input::GetKeyDown(Alpha::KeyCode::Space))
		{
			std::vector<glm::vec3> vertices =
			{
				{ 0.0f,   0.5f, 0.0f},
				{ 0.5f,   0.0f, 0.0f},
				{ 0.25f, -0.5f, 0.0f},
				{-0.25f, -0.5f, 0.0f},
				{-0.5f,   0.0f, 0.0f}
			};
			std::vector<glm::vec4> colors =
			{
				GetColor(255, 255, 0, 255),
				GetColor(255,   0, 0, 255),
				GetColor(  0,   0, 0, 255),
				GetColor(  0,   0, 0, 255),
				GetColor(  0, 255, 0, 255)
			};
			std::vector<uint32_t> triangles =
			{
				0, 1, 2,
				0, 2, 3,
				0, 3, 4
			};

			m_Mesh->SetVertices(vertices);
			m_Mesh->SetColors(colors);
			m_Mesh->SetTriangles(triangles);
		}

		Alpha::Renderer::Submit(m_Command);
	}

	virtual void OnEvent(Alpha::Event& e) override
	{
		Alpha::App::OnEvent(e);
	}

private:
	Alpha::MaterialRef m_Mat;
	Alpha::Texture2DRef m_FaceTex;
	Alpha::Texture2DRef m_WoodTex;
	Alpha::ShaderRef m_Shader;
	Alpha::MeshRef m_Mesh;
	Alpha::RenderMeshMaterialCommandRef m_Command;
};

Alpha::App* Alpha::CreateApp()
{
	return new Editor();
}

void Alpha::DestroyApp(Alpha::App*& app)
{
	if (app == nullptr) return;
	delete app;
	app = nullptr;
}