#include "InariKonKon/Graphics/Shader/Shader.hpp"

#include <vector>
#include <print>
#include <span>

#include "InariKonKon/Graphics/OpenGL/OpenGL.hpp"

namespace ikk
{
	Shader::Shader(const char* vertex, const char* fragment) noexcept
	{
		std::uint32_t vertexID = 0, fragmentID = 0;
		//vertex shader
		vertexID = gl->CreateShader(GL_VERTEX_SHADER);
		gl->ShaderSource(vertexID, 1, &vertex, 0);
		gl->CompileShader(vertexID);
		if (this->checkErrors(vertexID, false))
		{
			gl->DeleteShader(vertexID);
			return;
		}
		//fragment Shader
		fragmentID = gl->CreateShader(GL_FRAGMENT_SHADER);
		gl->ShaderSource(fragmentID, 1, &fragment, 0);
		gl->CompileShader(fragmentID);
		if (this->checkErrors(fragmentID, false))
		{
			gl->DeleteShader(vertexID);
			gl->DeleteShader(fragmentID);
			return;
		}
		//shader Program
		*this->m_id = gl->CreateProgram();
		gl->AttachShader(this->getNativeHandle(), vertexID);
		gl->AttachShader(this->getNativeHandle(), fragmentID);
		gl->LinkProgram(this->getNativeHandle());
		if (this->checkErrors(this->getNativeHandle(), true))
			gl->DeleteProgram(this->getNativeHandle());

		gl->DeleteShader(vertexID);
		gl->DeleteShader(fragmentID);
	}

	Shader::~Shader() noexcept
	{
		this->release();
	}

	void Shader::bind() const noexcept
	{
		gl->UseProgram(this->getNativeHandle());
	}

	void Shader::unbind() const noexcept
	{
		gl->UseProgram(0);
	}

	void Shader::release() const noexcept
	{
		if (this->canBeDeleted())
			gl->DeleteProgram(this->getNativeHandle());
	}

	void Shader::setBool(const std::string_view name, const bool value) const noexcept
	{
		this->bind();
		gl->Uniform1i(gl->GetUniformLocation(this->getNativeHandle(), name.data()), static_cast<int>(value));
	}

	void Shader::setInt(const std::string_view name, const int value) const noexcept
	{
		this->bind();
		gl->Uniform1i(gl->GetUniformLocation(this->getNativeHandle(), name.data()), value);
	}

	void Shader::setFloat(const std::string_view name, const float value) const noexcept
	{
		this->bind();
		gl->Uniform1f(gl->GetUniformLocation(this->getNativeHandle(), name.data()), value);
	}

	void Shader::setMatrix4x4(const std::string_view name, const mat4x4& matrix) const noexcept
	{
		this->bind();
		gl->UniformMatrix4fv(gl->GetUniformLocation(this->getNativeHandle(), name.data()), 1, GL_FALSE, &matrix.at(0, 0));
	}

	void Shader::setTexture(const std::string_view name, const Texture& texture) const noexcept
	{
		this->bind();
		gl->Uniform1i(gl->GetUniformLocation(this->getNativeHandle(), name.data()), texture.getTextureSlot());
	}

	void Shader::setCamera(const Camera<Projection::Perspective>& camera, const float aspectRatio, const std::uint32_t binding) const noexcept
	{
		this->bind();
		//TODO:
		//If camera did not change don't set it & since it's a uniform buffer u only need to set it once every camera movement!
		gl->UniformBlockBinding(this->getNativeHandle(), gl->GetUniformBlockIndex(this->getNativeHandle(), "Camera"), binding);
		this->m_uniformBuffer.BufferData(std::span<const mat4x4, 2>{ { camera.getProjectionMatrix(aspectRatio), camera.getViewMatrix() } }, binding);
	}

	void Shader::setCamera(const Camera<Projection::Ortho>& camera, const FloatRect viewRect, const std::uint32_t binding) const noexcept
	{
		this->bind();
		//TODO:
		//If camera did not change don't set it & since it's a uniform buffer u only need to set it once every camera movement!
		gl->UniformBlockBinding(this->getNativeHandle(), gl->GetUniformBlockIndex(this->getNativeHandle(), "Camera"), binding);
		this->m_uniformBuffer.BufferData(std::span<const mat4x4, 2>{ { camera.getProjectionMatrix(viewRect), camera.getViewMatrix() } }, binding);
	}

	Shader& Shader::getDefaultShaderProgram() noexcept
	{
		static const std::string defaultVS =
R"(#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;

out vec4 outColor;
out vec2 outTexCoord;

layout (std140, binding = 0) uniform Camera
{
	mat4 projection;
	mat4 view;
};

uniform mat4 model;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);
	outColor = color;
	outTexCoord = texCoord;
})";

		static const std::string defaultFS =
R"(#version 460 core

out vec4 FragColor;

in vec4 outColor;
in vec2 outTexCoord;

layout(binding = 0) uniform sampler2D tex;

void main()
{
	FragColor = texture(tex, outTexCoord) * outColor;
})";

		static Shader defaultProgram(defaultVS.c_str(), defaultFS.c_str());
		return defaultProgram;
	}

	const bool Shader::checkErrors(const std::uint32_t id, const bool isProgram) const noexcept
	{
		int success = 0;
		int maxLength = 0;
		if (isProgram == false)
		{
			gl->GetShaderiv(id, GL_COMPILE_STATUS, &success);
			if (success == GL_FALSE)
			{
				gl->GetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
				std::vector<char> infoLog(maxLength);
				gl->GetShaderInfoLog(id, maxLength, &maxLength, &infoLog[0]);
				for (const char& c : infoLog)
					std::print("{}", c);
				return true;
			}
		}
		else
		{
			gl->GetProgramiv(id, GL_LINK_STATUS, (int*)&success);
			if (success == GL_FALSE)
			{
				gl->GetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);
				std::vector<char> infoLog(maxLength);
				gl->GetProgramInfoLog(id, maxLength, &maxLength, &infoLog[0]);
				for (const char& c : infoLog)
					std::print("{}", c);
				return true;
			}
		}
		return false;
	}
}