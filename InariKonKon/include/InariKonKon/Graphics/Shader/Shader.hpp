#pragma once

#include <string_view>

#include "InariKonKon/Graphics/OpenGLObject.hpp"

namespace ikk
{
	class Shader final : public priv::OpenGLObject
	{
	public:
		Shader(const char* vertex, const char* fragment) noexcept;

		Shader(const Shader&) noexcept = default;
		Shader(Shader&) noexcept = default;
		Shader(Shader&&) noexcept = default;

		Shader& operator=(const Shader&) noexcept = default;
		Shader& operator=(Shader&) noexcept = default;
		Shader& operator=(Shader&&) noexcept = default;

		~Shader() noexcept;

		void bind() noexcept;
		void unbind() noexcept;

		void setBool(const std::string_view name, const bool value) const noexcept;
		void setInt(const std::string_view name, const int value) const noexcept;
		void setFloat(const std::string_view name, const float value) const noexcept;
	private:
		const bool checkErrors(const std::uint32_t id, const bool isProgram) const noexcept;
	};
}