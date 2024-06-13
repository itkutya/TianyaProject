module;

#include "InariKonKon/Graphics/OpenGL.hpp"

export module Shader;

import <string_view>;
import <vector>;
import <print>;
import <span>;

import OpenGLObject;
import Texture;
import Matrix;
import Camera;
import Window;

export namespace ikk
{
	class Shader final : public OpenGLObject
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
		void setCamera(const Window& window, const Camera<Projection::Perspective>& camera, const std::uint32_t binding = 0) const noexcept;
		void setCamera(const Window& window, const Camera<Projection::Ortho>& camera, const std::uint32_t binding = 0) const noexcept;

		static Shader& getDefaultShaderProgram() noexcept;
	private:
		const bool checkErrors(const std::uint32_t id, const bool isProgram) const noexcept;
	};

	Shader::Shader(const char* vertex, const char* fragment) noexcept
	{
		std::uint32_t vertexID = 0, fragmentID = 0;
		//vertex shader
		vertexID = gl->CreateShader(GL_VERTEX_SHADER);
		gl->ShaderSource(vertexID, 1, &vertex, 0);
		gl->CompileShader(vertexID);
		if (this->checkErrors(vertexID, false) == true)
		{
			gl->DeleteShader(vertexID);
			return;
		}
		//fragment Shader
		fragmentID = gl->CreateShader(GL_FRAGMENT_SHADER);
		gl->ShaderSource(fragmentID, 1, &fragment, 0);
		gl->CompileShader(fragmentID);
		if (this->checkErrors(fragmentID, false) == true)
		{
			gl->DeleteShader(vertexID);
			gl->DeleteShader(fragmentID);
			return;
		}
		//shader Program
		this->m_id = gl->CreateProgram();
		gl->AttachShader(this->m_id, vertexID);
		gl->AttachShader(this->m_id, fragmentID);
		gl->LinkProgram(this->m_id);
		if (this->checkErrors(this->m_id, true) == true)
			gl->DeleteProgram(this->m_id);

		gl->DeleteShader(vertexID);
		gl->DeleteShader(fragmentID);
	}

	Shader::~Shader() noexcept
	{
		this->release();
	}

	void Shader::bind() const noexcept
	{
		gl->UseProgram(this->m_id);
	}

	void Shader::unbind() const noexcept
	{
		gl->UseProgram(0);
	}

	void Shader::release() const noexcept
	{
		if (this->m_id)
			gl->DeleteProgram(this->m_id);
		this->m_id = 0;
	}
	
	void Shader::setBool(const std::string_view name, const bool value) const noexcept
	{
		this->bind();
		gl->Uniform1i(gl->GetUniformLocation(this->m_id, name.data()), static_cast<int>(value));
	}

	void Shader::setInt(const std::string_view name, const int value) const noexcept
	{
		this->bind();
		gl->Uniform1i(gl->GetUniformLocation(this->m_id, name.data()), value);
	}

	void Shader::setFloat(const std::string_view name, const float value) const noexcept
	{
		this->bind();
		gl->Uniform1f(gl->GetUniformLocation(this->m_id, name.data()), value);
	}

	void Shader::setMatrix4x4(const std::string_view name, const mat4x4& matrix) const noexcept
	{
		this->bind();
		gl->UniformMatrix4fv(gl->GetUniformLocation(this->m_id, name.data()), 1, GL_FALSE, &matrix.at<0, 0>());
	}

	void Shader::setTexture(const std::string_view name, const Texture& texture) const noexcept
	{
		this->bind();
		gl->Uniform1i(gl->GetUniformLocation(this->m_id, name.data()), texture.getTextureSlot());
	}

	void Shader::setCamera(const Window& window, const Camera<Projection::Perspective>& camera, const std::uint32_t binding) const noexcept
	{
		this->bind();
		gl->UniformBlockBinding(this->m_id, gl->GetUniformBlockIndex(this->m_id, "Camera"), binding);
		camera.getUniformBuffer().BufferData(std::span<const mat4x4, 2>{ { camera.getProjectionMatrix(window.getAspectRatio()), camera.getViewMatrix() } }, binding);
	}

	void Shader::setCamera(const Window& window, const Camera<Projection::Ortho>& camera, const std::uint32_t binding) const noexcept
	{
		this->bind();
		gl->UniformBlockBinding(this->m_id, gl->GetUniformBlockIndex(this->m_id, "Camera"), binding);
		camera.getUniformBuffer().BufferData(std::span<const mat4x4, 2>{ { camera.getProjectionMatrix({ 1.f, 1.f, -1.f, -1.f }), camera.getViewMatrix() } }, binding);
	}

	Shader& Shader::getDefaultShaderProgram() noexcept
	{
		static std::string defaultVS =
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

		static std::string defaultFS =
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