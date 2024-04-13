#include "InariKonKon/Graphics/Shader/Shader.hpp"

#include <vector>
#include <print>

#include "InariKonKon/Window/Context/Context.h"

ikk::Shader::Shader(const char* vertex, const char* fragment) noexcept
{
    std::uint32_t vertexID = 0, fragmentID = 0;
    //vertex shader
    vertexID = priv::Context::getInstance().getContext().CreateShader(GL_VERTEX_SHADER);
    priv::Context::getInstance().getContext().ShaderSource(vertexID, 1, &vertex, NULL);
    priv::Context::getInstance().getContext().CompileShader(vertexID);
    if (this->checkErrors(vertexID, false) == true)
    {
        priv::Context::getInstance().getContext().DeleteShader(vertexID);
        return;
    }
    //fragment Shader
    fragmentID = priv::Context::getInstance().getContext().CreateShader(GL_FRAGMENT_SHADER);
    priv::Context::getInstance().getContext().ShaderSource(fragmentID, 1, &fragment, NULL);
    priv::Context::getInstance().getContext().CompileShader(fragmentID);
    if (this->checkErrors(fragmentID, false) == true)
    {
        priv::Context::getInstance().getContext().DeleteShader(vertexID);
        priv::Context::getInstance().getContext().DeleteShader(fragmentID);
        return;
    }
    //shader Program
    this->m_id = priv::Context::getInstance().getContext().CreateProgram();
    priv::Context::getInstance().getContext().AttachShader(this->m_id, vertexID);
    priv::Context::getInstance().getContext().AttachShader(this->m_id, fragmentID);
    priv::Context::getInstance().getContext().LinkProgram(this->m_id);
    if (this->checkErrors(this->m_id, true) == true)
        priv::Context::getInstance().getContext().DeleteProgram(this->m_id);

    priv::Context::getInstance().getContext().DeleteShader(vertexID);
    priv::Context::getInstance().getContext().DeleteShader(fragmentID);
}

ikk::Shader::~Shader() noexcept
{
    priv::Context::getInstance().getContext().DeleteProgram(this->m_id);
}

void ikk::Shader::bind() noexcept
{
    priv::Context::getInstance().getContext().UseProgram(this->m_id);
}

void ikk::Shader::unbind() noexcept
{
    priv::Context::getInstance().getContext().UseProgram(0);
}

void ikk::Shader::setBool(const std::string_view name, const bool value) const noexcept
{
    priv::Context::getInstance().getContext().Uniform1i(priv::Context::getInstance().getContext().GetUniformLocation(this->m_id, name.data()), static_cast<int>(value));
}

void ikk::Shader::setInt(const std::string_view name, const int value) const noexcept
{
    priv::Context::getInstance().getContext().Uniform1i(priv::Context::getInstance().getContext().GetUniformLocation(this->m_id, name.data()), value);
}

void ikk::Shader::setFloat(const std::string_view name, const float value) const noexcept
{
    priv::Context::getInstance().getContext().Uniform1f(priv::Context::getInstance().getContext().GetUniformLocation(this->m_id, name.data()), value);
}

const bool ikk::Shader::checkErrors(const std::uint32_t id, const bool isProgram) const noexcept
{
    int success = 0;
    int maxLength = 0;
    if (isProgram == false)
    {
        priv::Context::getInstance().getContext().GetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE)
        {
            priv::Context::getInstance().getContext().GetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<char> infoLog(maxLength);
            priv::Context::getInstance().getContext().GetShaderInfoLog(id, maxLength, &maxLength, &infoLog[0]);
            for (const char& c : infoLog)
                std::print("{}", c);
            return true;
        }
    }
    else
    {
        priv::Context::getInstance().getContext().GetProgramiv(id, GL_LINK_STATUS, (int*)&success);
        if (success == GL_FALSE)
        {
            priv::Context::getInstance().getContext().GetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<char> infoLog(maxLength);
            priv::Context::getInstance().getContext().GetProgramInfoLog(id, maxLength, &maxLength, &infoLog[0]);
            for (const char& c : infoLog)
                std::print("{}", c);
            return true;
        }
    }
    return false;
}