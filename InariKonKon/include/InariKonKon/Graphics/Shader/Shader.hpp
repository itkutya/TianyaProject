#pragma once

#include <string_view>

#include "InariKonKon/Graphics/OpenGLObject.hpp"

namespace ikk
{
	class Shader final : public priv::OpenGLObject
	{
	public:
		Shader(const char* vertex, const char* fragment) noexcept;
		~Shader() noexcept;

		void bind() noexcept override;
		void unbind() noexcept override;
		void release() noexcept override;

		void setBool(const std::string_view name, const bool value) const noexcept;
		void setInt(const std::string_view name, const int value) const noexcept;
		void setFloat(const std::string_view name, const float value) const noexcept;

		static Shader& getDefaultShaderProgram() noexcept;
	private:
		const bool checkErrors(const std::uint32_t id, const bool isProgram) const noexcept;
	};
}