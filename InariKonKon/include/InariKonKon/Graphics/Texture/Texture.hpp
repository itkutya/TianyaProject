#pragma once

#include <filesystem>

#include "InariKonKon/Graphics/OpenGL/OpenGLObject.hpp"
#include "InariKonKon/Utility/Math/Vector2.hpp"
#include "InariKonKon/Graphics/OpenGL/OpenGL.hpp"

namespace ikk
{
	class Texture : public priv::OpenGLObject
	{
	public:
		enum class Type : std::uint32_t
		{
			Red = GL_RED, Green = GL_GREEN, Blue = GL_BLUE, Aplha = GL_ALPHA, RGB = GL_RGB, RGBA = GL_RGBA
		};

		enum class Wrapping : std::uint32_t
		{
			ClampToEdge = GL_CLAMP_TO_EDGE, ClampToBorder = GL_CLAMP_TO_BORDER, Mirrored_Repeat = GL_MIRRORED_REPEAT, Repeat = GL_REPEAT, MirrorClampToEdge = GL_MIRROR_CLAMP_TO_EDGE
		};

		enum class MinFilter : std::uint32_t
		{
			Nearest = GL_NEAREST, Linear = GL_LINEAR, NearestMipMapNearest = GL_NEAREST_MIPMAP_NEAREST, LinearMipMapNearest = GL_LINEAR_MIPMAP_NEAREST,
			NearestMipMapLinear = GL_NEAREST_MIPMAP_LINEAR, LinearMipMapLinear = GL_LINEAR_MIPMAP_LINEAR
		};

		enum class MagFilter : std::uint32_t
		{
			Nearest = GL_NEAREST, Linear = GL_LINEAR
		};

		struct Settings
		{
			Type type = Type::RGB;
			Wrapping wrapping = Wrapping::Repeat;
			MinFilter minFilter = MinFilter::Nearest;
			MagFilter magFilter = MagFilter::Nearest;
			bool generateMipMap = true;
		};

		Texture(const Texture::Settings settings = {}, const std::uint32_t slot = 0) noexcept;
		Texture(const vec2u size, const Texture::Settings settings = {}, const std::uint32_t slot = 0) noexcept;
		Texture(const std::filesystem::path path, const Texture::Settings settings = {}, const std::uint32_t slot = 0) noexcept;
		~Texture() noexcept;

		void bind() const noexcept override;
		void unbind() const noexcept override;
		void release() const noexcept override;

		const bool loadFromDisc(const std::filesystem::path path) noexcept;
		const bool loadFromMemory(const std::uint8_t* const data) noexcept;

		const std::uint32_t& getTextureSlot() const noexcept;
		
		void create(const vec2u size) noexcept;
	private:
		std::uint32_t m_slot;
		Settings m_settings;

		std::uint32_t m_width = 0;
		std::uint32_t m_height = 0;
		std::uint32_t m_channels = 0;
		std::uint8_t* m_data = nullptr;

		void setUpSettings() const noexcept;
	};
}