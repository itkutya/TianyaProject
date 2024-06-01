#pragma once

#include <string_view>

#include "InariKonKon/Graphics/Texture/Texture.hpp"
#include "InariKonKon/Graphics/Camera/Camera.hpp"
#include "InariKonKon/Graphics/OpenGLObject.hpp"
#include "InariKonKon/Utility/Math/Matrix.hpp"

namespace ikk
{
	class Window;

	class Shader final : public priv::OpenGLObject
	{
	public:
		//Add shaderbuilder constructor...
		Shader(const char* vertex, const char* fragment) noexcept;
		~Shader() noexcept;

		void bind() const noexcept override;
		void unbind() const noexcept override;
		void release() const noexcept override;

		void setBool(const std::string_view name, const bool value) const noexcept;
		void setInt(const std::string_view name, const int value) const noexcept;
		void setFloat(const std::string_view name, const float value) const noexcept;
		void setMatrix4x4(const std::string_view name, const mat4x4& matrix) const noexcept;
		void setTexture(const std::string_view name, const Texture& texture) const noexcept;
		void setCamera(const Window& window, const Camera<Projection::Perspective>& camera) const noexcept;
		void setCamera(const Window& window, const Camera<Projection::Orhto>& camera) const noexcept;

		static Shader& getDefaultShaderProgram() noexcept;
	private:
		const bool checkErrors(const std::uint32_t id, const bool isProgram) const noexcept;
	};
}