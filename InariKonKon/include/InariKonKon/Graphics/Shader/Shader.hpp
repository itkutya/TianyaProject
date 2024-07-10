#pragma once

#include <string_view>

#include "InariKonKon/Graphics/Buffers/UniformBuffer.hpp"
#include "InariKonKon/Graphics/OpenGL/OpenGLObject.hpp"
#include "InariKonKon/Graphics/Draw/DrawEnums.hpp"
#include "InariKonKon/Utility/Math/Matrix.hpp"
#include "InariKonKon/Utility/Math/Rect.hpp"

namespace ikk
{
	class Texture;
	template<Projection P>
	class Camera;

	class Shader final : public priv::OpenGLObject
	{
	public:
		//TODO:
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
		void setCamera(const Camera<Projection::Perspective>& camera, const float aspectRatio, const std::uint32_t binding = 0) const noexcept;
		void setCamera(const Camera<Projection::Ortho>& camera, const Rect<float> viewRect, const std::uint32_t binding = 0) const noexcept;

		static Shader& getDefaultShaderProgram() noexcept;
	private:
		const bool checkErrors(const std::uint32_t id, const bool isProgram) const noexcept;

		//TODO:
		//Use unordered map with binding points? idk...
		priv::UniformBuffer m_uniformBuffer{ GL_DYNAMIC_DRAW };
	};
}