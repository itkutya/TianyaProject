#pragma once

#include <filesystem>

#include "InariKonKon/Graphics/OpenGL/OpenGLObject.hpp"
#include "InariKonKon/Utility/Math/Vector2.hpp"

namespace ikk
{
	class Texture : public priv::OpenGLObject
	{
	public:
		Texture(const std::uint32_t slot = 0) noexcept;
		Texture(const std::filesystem::path path, const std::uint32_t slot = 0) noexcept;
		~Texture() noexcept;

		void bind() const noexcept override;
		void unbind() const noexcept override;
		void release() const noexcept override;

		void create(const vec2u size) noexcept;

		const bool loadFromDisc(const std::filesystem::path path) noexcept;
		const bool loadFromMemory(const std::uint8_t* const data) noexcept;

		const std::uint32_t& getTextureSlot() const noexcept;
	private:
		std::uint32_t m_slot;
		std::uint32_t m_width = 0;
		std::uint32_t m_height = 0;
		std::uint32_t m_channels = 0;
		std::uint8_t* m_data = nullptr;
	};
}