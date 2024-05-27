#include "InariKonKon/Graphics/Shader/Shader.hpp"

#include <vector>
#include <print>

#include "InariKonKon/Graphics/OpenGL.hpp"

ikk::Shader::Shader(const char* vertex, const char* fragment) noexcept
{
    std::uint32_t vertexID = 0, fragmentID = 0;
    //vertex shader
    vertexID = gl->CreateShader(GL_VERTEX_SHADER);
    gl->ShaderSource(vertexID, 1, &vertex, NULL);
    gl->CompileShader(vertexID);
    if (this->checkErrors(vertexID, false) == true)
    {
        gl->DeleteShader(vertexID);
        return;
    }
    //fragment Shader
    fragmentID = gl->CreateShader(GL_FRAGMENT_SHADER);
    gl->ShaderSource(fragmentID, 1, &fragment, NULL);
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

ikk::Shader::~Shader() noexcept
{
    this->release();
}

void ikk::Shader::bind() const noexcept
{
    gl->UseProgram(this->m_id);
}

void ikk::Shader::unbind() const noexcept
{
    gl->UseProgram(0);
}

void ikk::Shader::release() const noexcept
{
    if (this->m_id)
        gl->DeleteProgram(this->m_id);
    this->m_id = 0;
}

void ikk::Shader::setBool(const std::string_view name, const bool value) const noexcept
{
    this->bind();
    gl->Uniform1i(gl->GetUniformLocation(this->m_id, name.data()), static_cast<int>(value));
}

void ikk::Shader::setInt(const std::string_view name, const int value) const noexcept
{
    this->bind();
    gl->Uniform1i(gl->GetUniformLocation(this->m_id, name.data()), value);
}

void ikk::Shader::setFloat(const std::string_view name, const float value) const noexcept
{
    this->bind();
    gl->Uniform1f(gl->GetUniformLocation(this->m_id, name.data()), value);
}

void ikk::Shader::setMatrix4x4(const std::string_view name, const mat4x4& matrix) const noexcept
{
    this->bind();
    gl->UniformMatrix4fv(gl->GetUniformLocation(this->m_id, name.data()), 1, GL_FALSE, &matrix[0][0]);
}

void ikk::Shader::setTexture(const std::string_view name, const Texture& texture) const noexcept
{
    this->bind();
    gl->Uniform1i(gl->GetUniformLocation(this->m_id, name.data()), texture.getTextureSlot());
}

ikk::Shader& ikk::Shader::getDefaultShaderProgram() noexcept
{
    static std::string defaultVS =
R"(#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;

out vec4 outColor;
out vec2 outTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

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

const bool ikk::Shader::checkErrors(const std::uint32_t id, const bool isProgram) const noexcept
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