#pragma once

#include <span>

#include "InariKonKon/Graphics/OpenGLObject.hpp"
#include "InariKonKon/Graphics/Drawable.hpp"

namespace ikk
{
	namespace priv
	{
		class ElementBufferObject final : public OpenGLObject
		{
		public:
			ElementBufferObject(const std::span<std::uint32_t> indices, const Drawable::Type type = Drawable::Type::STATIC_DRAW) noexcept;

			ElementBufferObject(const ElementBufferObject&) noexcept = default;
			ElementBufferObject(ElementBufferObject&) noexcept = default;
			ElementBufferObject(ElementBufferObject&&) noexcept = default;

			ElementBufferObject& operator=(const ElementBufferObject&) noexcept = default;
			ElementBufferObject& operator=(ElementBufferObject&) noexcept = default;
			ElementBufferObject& operator=(ElementBufferObject&&) noexcept = default;

			~ElementBufferObject() noexcept;

			void bind() noexcept override;
			void unbind() noexcept override;
		private:
		};
	}
}