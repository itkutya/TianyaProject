#pragma once

#include <filesystem>

#include "InariKonKon/Graphics/OpenGLObject.hpp"
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

		template<priv::Number T>
		void create(const Vector2<T> size) noexcept;

		const bool loadFromDisc(const std::filesystem::path path) noexcept;
		const bool loadFromMemory(const std::uint8_t* const data) noexcept;
	private:
		std::uint32_t m_slot;
		int m_width = 0;
		int m_height = 0;
		int m_channels = 0;
		std::uint8_t* m_data = nullptr;

		void createImpl() noexcept;
	};

	template<priv::Number T>
	inline void Texture::create(const Vector2<T> size) noexcept
	{
		this->m_width = static_cast<int>(size.x);
		this->m_height = static_cast<int>(size.y);
		this->createImpl();
	}
}