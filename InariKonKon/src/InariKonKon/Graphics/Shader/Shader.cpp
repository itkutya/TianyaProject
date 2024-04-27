#include "InariKonKon/Graphics/Shader/Shader.hpp"

#include <vector>
#include <print>

#include "InariKonKon/Window/Context/Context.hpp"

inline constexpr const char* defaultVS =   "#version 460 core\n"
                                            "layout (location = 0) in vec3 position;\n"
                                            "layout (location = 1) in vec4 color;\n"
                                            "layout (location = 2) in vec2 texCoord;\n"
                                            "out vec4 outColor;\n"
                                            "out vec2 outTexCoord;\n"
                                            "void main()\n"
                                            "{\n"
                                            "	gl_Position = vec4(position, 1.0);\n"
                                            "	outColor = color;\n"
                                            "	outTexCoord = texCoord;\n"
                                            "}\0";

inline constexpr const char* defaultFS =    "#version 460 core\n"
                                            "out vec4 FragColor;\n"
                                            "in vec4 outColor;\n"
                                            "in vec2 outTexCoord;\n"
                                            "void main()\n"
                                            "{\n"
                                            "	FragColor = outColor;\n"
                                            "}\n\0";

ikk::Shader::Shader() noexcept
{
    std::uint32_t vertexID = 0, fragmentID = 0;
    //vertex shader
    vertexID = gl->CreateShader(GL_VERTEX_SHADER);
    gl->ShaderSource(vertexID, 1, &defaultVS, NULL);
    gl->CompileShader(vertexID);
    if (this->checkErrors(vertexID, false) == true)
    {
        gl->DeleteShader(vertexID);
        return;
    }
    //fragment Shader
    fragmentID = gl->CreateShader(GL_FRAGMENT_SHADER);
    gl->ShaderSource(fragmentID, 1, &defaultFS, NULL);
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

void ikk::Shader::bind() noexcept
{
    gl->UseProgram(this->m_id);
}

void ikk::Shader::unbind() noexcept
{
    gl->UseProgram(0);
}

void ikk::Shader::release() noexcept
{
    if (this->m_id)
        gl->DeleteProgram(this->m_id);
    this->m_id = 0;
}

void ikk::Shader::setBool(const std::string_view name, const bool value) const noexcept
{
    gl->Uniform1i(gl->GetUniformLocation(this->m_id, name.data()), static_cast<int>(value));
}

void ikk::Shader::setInt(const std::string_view name, const int value) const noexcept
{
    gl->Uniform1i(gl->GetUniformLocation(this->m_id, name.data()), value);
}

void ikk::Shader::setFloat(const std::string_view name, const float value) const noexcept
{
    gl->Uniform1f(gl->GetUniformLocation(this->m_id, name.data()), value);
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