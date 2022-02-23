#include "pch.h"
#include "Alpha/Graphics/Texture.h"

#include <glad/glad.h>

namespace Alpha
{
	Texture2DRef Texture2D::CreateRef(const glm::uvec2& size)
	{
		Texture2DRef texture(new Texture2D(size));
		return texture;
	}

	Texture2DRef Texture2D::CreateRef(const glm::uvec2& size, TextureFormat format)
	{
		Texture2DRef texture(new Texture2D(size, format));
		return texture;
	}

	Texture2DRef Texture2D::CreateRef(const glm::uvec2& size, TextureFormat format, const unsigned char* pixels)
	{
		Texture2DRef texture(new Texture2D(size, format, pixels));
		return texture;
	}

	Texture2DRef Texture2D::CreateRef(const glm::uvec2& size, TextureFormat format, const float* pixels)
	{
		Texture2DRef texture(new Texture2D(size, format, pixels));
		return texture;
	}

	Texture2D::Texture2D(const glm::uvec2& size) :
		m_Size(size), m_BorderColor(0.5f, 0.5f, 0.5f, 1.0f)
	{
		m_WrapMode = WrapMode::Repeat;
		m_FilterMode = FilterMode::Nearest;
		m_MipmapMode = MipmapMode::NearestMipmapNearest;
		m_Format = TextureFormat::RGB;

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, (int)m_Format, m_Size.x, m_Size.y, 0, (GLenum)m_Format, GL_UNSIGNED_BYTE, nullptr);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture2D::Texture2D(const glm::uvec2& size, TextureFormat format) :
		m_Size(size), m_BorderColor(0.5f, 0.5f, 0.5f, 1.0f)
	{
		m_WrapMode = WrapMode::Repeat;
		m_FilterMode = FilterMode::Nearest;
		m_MipmapMode = MipmapMode::NearestMipmapNearest;
		m_Format = format;

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, (int)m_Format, m_Size.x, m_Size.y, 0, (GLenum)m_Format, GL_UNSIGNED_BYTE, nullptr);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture2D::Texture2D(const glm::uvec2& size, TextureFormat format, const unsigned char* pixels) :
		m_Size(size), m_BorderColor(0.5f, 0.5f, 0.5f, 1.0f)
	{
		m_WrapMode = WrapMode::Repeat;
		m_FilterMode = FilterMode::Nearest;
		m_MipmapMode = MipmapMode::NearestMipmapNearest;
		m_Format = format;

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, (int)m_Format, m_Size.x, m_Size.y, 0, (GLenum)m_Format, GL_UNSIGNED_BYTE, pixels);
		if (pixels) glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture2D::Texture2D(const glm::uvec2& size, TextureFormat format, const float* pixels) :
		m_Size(size), m_BorderColor(0.5f, 0.5f, 0.5f, 1.0f)
	{
		m_WrapMode = WrapMode::Repeat;
		m_FilterMode = FilterMode::Nearest;
		m_MipmapMode = MipmapMode::NearestMipmapNearest;
		m_Format = format;

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, (int)m_Format, m_Size.x, m_Size.y, 0, (GLenum)m_Format, GL_FLOAT, pixels);
		if (pixels) glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_TextureID);
	}

	void Texture2D::Resize(const glm::uvec2& size)
	{
		m_Size = size;
	}

	void Texture2D::SetPixels(const unsigned char* pixels)
	{
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexImage2D(GL_TEXTURE_2D, 0, (int)m_Format, m_Size.x, m_Size.y, 0, (GLenum)m_Format, GL_UNSIGNED_BYTE, pixels);
		if (pixels) glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture2D::SetPixels(const float* pixels)
	{
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexImage2D(GL_TEXTURE_2D, 0, (int)m_Format, m_Size.x, m_Size.y, 0, (GLenum)m_Format, GL_FLOAT, pixels);
		if (pixels) glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture2D::SetBorderColor(const glm::vec4& color)
	{
		m_BorderColor = color;
	}

	void Texture2D::SetWrapMode(WrapMode mode)
	{
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		switch (mode)
		{
			case Alpha::WrapMode::Repeat:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				break;
			case Alpha::WrapMode::MirroredRepeat:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
				break;
			case Alpha::WrapMode::ClampToEdge:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				break;
			case Alpha::WrapMode::ClampToBorder:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
				glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, &m_BorderColor[0]);
				break;
		}

		glBindTexture(GL_TEXTURE_2D, 0);

		m_WrapMode = mode;
	}

	void Texture2D::SetFilterMode(FilterMode mode)
	{
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		switch (mode)
		{
			case Alpha::FilterMode::Nearest:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				break;
			case Alpha::FilterMode::Linear:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				break;
			case Alpha::FilterMode::NearestAndLinear:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				break;
			case Alpha::FilterMode::LinearAndNearest:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				break;
		}

		glBindTexture(GL_TEXTURE_2D, 0);

		m_FilterMode = mode;
	}

	void Texture2D::SetMipmapMode(MipmapMode mode)
	{
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		switch (mode)
		{
			case Alpha::MipmapMode::NearestMipmapNearest:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
				break;
			case Alpha::MipmapMode::NearestMipmapLinear:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
				break;
			case Alpha::MipmapMode::LinearMipmapNearest:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
				break;
			case Alpha::MipmapMode::LinearMipmapLinear:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				break;
		}

		glBindTexture(GL_TEXTURE_2D, 0);

		m_MipmapMode = mode;
	}

	void Texture2D::SetTextureFormat(TextureFormat format)
	{
		m_Format = format;
	}

}