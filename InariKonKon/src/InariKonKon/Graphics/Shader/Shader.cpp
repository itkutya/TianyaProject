#include "InariKonKon/Graphics/Shader/Shader.hpp"

#include <vector>
#include <print>

#include "glad/gl.h"

#include "InariKonKon/Window/Context/Context.hpp"

ikk::Shader::Shader(const char* vertex, const char* fragment) noexcept
{
    std::uint32_t vertexID = 0, fragmentID = 0;
    //vertex shader
    vertexID = priv::gl()->CreateShader(GL_VERTEX_SHADER);
    priv::gl()->ShaderSource(vertexID, 1, &vertex, NULL);
    priv::gl()->CompileShader(vertexID);
    if (this->checkErrors(vertexID, false) == true)
    {
        priv::gl()->DeleteShader(vertexID);
        return;
    }
    //fragment Shader
    fragmentID = priv::gl()->CreateShader(GL_FRAGMENT_SHADER);
    priv::gl()->ShaderSource(fragmentID, 1, &fragment, NULL);
    priv::gl()->CompileShader(fragmentID);
    if (this->checkErrors(fragmentID, false) == true)
    {
        priv::gl()->DeleteShader(vertexID);
        priv::gl()->DeleteShader(fragmentID);
        return;
    }
    //shader Program
    this->m_id = priv::gl()->CreateProgram();
    priv::gl()->AttachShader(this->m_id, vertexID);
    priv::gl()->AttachShader(this->m_id, fragmentID);
    priv::gl()->LinkProgram(this->m_id);
    if (this->checkErrors(this->m_id, true) == true)
        priv::gl()->DeleteProgram(this->m_id);

    priv::gl()->DeleteShader(vertexID);
    priv::gl()->DeleteShader(fragmentID);
}

ikk::Shader::~Shader() noexcept
{
    priv::gl()->DeleteProgram(this->m_id);
}

void ikk::Shader::bind() noexcept
{
    priv::gl()->UseProgram(this->m_id);
}

void ikk::Shader::unbind() noexcept
{
    priv::gl()->UseProgram(0);
}

void ikk::Shader::setBool(const std::string_view name, const bool value) const noexcept
{
    priv::gl()->Uniform1i(priv::gl()->GetUniformLocation(this->m_id, name.data()), static_cast<int>(value));
}

void ikk::Shader::setInt(const std::string_view name, const int value) const noexcept
{
    priv::gl()->Uniform1i(priv::gl()->GetUniformLocation(this->m_id, name.data()), value);
}

void ikk::Shader::setFloat(const std::string_view name, const float value) const noexcept
{
    priv::gl()->Uniform1f(priv::gl()->GetUniformLocation(this->m_id, name.data()), value);
}

const bool ikk::Shader::checkErrors(const std::uint32_t id, const bool isProgram) const noexcept
{
    int success = 0;
    int maxLength = 0;
    if (isProgram == false)
    {
        priv::gl()->GetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE)
        {
            priv::gl()->GetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<char> infoLog(maxLength);
            priv::gl()->GetShaderInfoLog(id, maxLength, &maxLength, &infoLog[0]);
            for (const char& c : infoLog)
                std::print("{}", c);
            return true;
        }
    }
    else
    {
        priv::gl()->GetProgramiv(id, GL_LINK_STATUS, (int*)&success);
        if (success == GL_FALSE)
        {
            priv::gl()->GetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<char> infoLog(maxLength);
            priv::gl()->GetProgramInfoLog(id, maxLength, &maxLength, &infoLog[0]);
            for (const char& c : infoLog)
                std::print("{}", c);
            return true;
        }
    }
    return false;
}