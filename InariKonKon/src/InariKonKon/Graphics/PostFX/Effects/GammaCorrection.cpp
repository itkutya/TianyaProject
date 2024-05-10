#include "InariKonKon/Graphics/PostFX/Effects/GammaCorrection.hpp"

constexpr const char* gammaVS = "#version 460 core\n"
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
								"}";

constexpr const char* gammaFS =	"#version 460 core\n"
								"out vec4 FragColor;\n"
								"in vec4 outColor;\n"
								"in vec2 outTexCoord;\n"
								"uniform sampler2D scene;\n"
								"void main()\n"
								"{\n"
								"	FragColor = vec4(pow(texture(scene, outTexCoord), vec4(1.0 / 2.2)));\n"
								"}";

ikk::GammaCorrection::GammaCorrection() noexcept : PostFX(gammaVS, gammaFS)
{
	this->m_shader.bind();
	this->m_shader.setInt("scene", 0);
	this->m_shader.unbind();
}

void ikk::GammaCorrection::apply() noexcept
{
	this->m_shader.bind();
}