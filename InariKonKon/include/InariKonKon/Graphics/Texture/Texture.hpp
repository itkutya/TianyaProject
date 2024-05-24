#pragma once

#include <filesystem>

#include "InariKonKon/Graphics/OpenGLObject.hpp"

namespace ikk
{
	class Texture : public priv::OpenGLObject
	{
	public:
		Texture(const std::filesystem::path path, const std::uint32_t slot = 0) noexcept;
		~Texture() noexcept;

		void bind() const noexcept override;
		void unbind() const noexcept override;
		void release() const noexcept override;
	private:
		std::uint32_t m_slot = 0;
		int m_width = 0;
		int m_height = 0;
		int m_channels = 0;
		std::uint8_t* m_data = nullptr;
	};
}