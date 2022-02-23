#pragma once

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "Alpha/Macros.h"

namespace Alpha
{
	enum class WrapMode
	{
		Repeat			 = 0x2901,
		MirroredRepeat	 = 0x8370,
		ClampToEdge		 = 0x812F,
		ClampToBorder	 = 0x812D
	};

	enum class FilterMode
	{
		Nearest	 = 0x2600,
		Linear	 = 0x2601,
		NearestAndLinear,
		LinearAndNearest
	};

	enum class MipmapMode
	{
		NearestMipmapNearest	 = 0x2700,
		NearestMipmapLinear		 = 0x2702,
		LinearMipmapNearest		 = 0x2701,
		LinearMipmapLinear		 = 0x2703
	};

	enum class TextureFormat
	{
		RGB	 = 0x1907,
		RGBA = 0x1908
	};

	class Texture2D;
	DEF_SMART_POINTER(Texture2D);

	class Texture2D
	{
	public:
		~Texture2D();

		inline uint32_t GetID() const { return m_TextureID; }
		inline const glm::uvec2& GetSize() const { return m_Size; }
		inline const glm::vec4& GetBoderColor() const { return m_BorderColor; }
		inline WrapMode GetWrapMode() const { return m_WrapMode; }
		inline FilterMode GetFilterMode() const { return m_FilterMode; }
		inline MipmapMode GetMipmapMode() const { return m_MipmapMode; }
		inline TextureFormat GetTextureFormat() const { return m_Format; }

		void Resize(const glm::uvec2& size);
		void SetPixels(const unsigned char* pixels);
		void SetPixels(const float* pixels);
		void SetBorderColor(const glm::vec4& color);
		void SetWrapMode(WrapMode mode);
		void SetFilterMode(FilterMode mode);
		void SetMipmapMode(MipmapMode mode);
		void SetTextureFormat(TextureFormat format);

		static Texture2DRef CreateRef(const glm::uvec2& size);
		static Texture2DRef CreateRef(const glm::uvec2& size, TextureFormat format);
		static Texture2DRef CreateRef(const glm::uvec2& size, TextureFormat format, const float* pixels);
		static Texture2DRef CreateRef(const glm::uvec2& size, TextureFormat format, const unsigned char* pixels);

	private:
		Texture2D(const glm::uvec2& size);
		Texture2D(const glm::uvec2& size, TextureFormat format);
		Texture2D(const glm::uvec2& size, TextureFormat format, const float* pixels);
		Texture2D(const glm::uvec2& size, TextureFormat format, const unsigned char* pixels);

	private:
		uint32_t m_TextureID;
		glm::uvec2 m_Size;
		glm::vec4 m_BorderColor;
		WrapMode m_WrapMode;
		FilterMode m_FilterMode;
		MipmapMode m_MipmapMode;
		TextureFormat m_Format;
	};
}