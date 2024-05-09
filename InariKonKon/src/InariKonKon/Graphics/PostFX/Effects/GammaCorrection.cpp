#include "InariKonKon/Graphics/PostFX/Effects/GammaCorrection.h"

constexpr const char* gammaVS =	"#version 460 core\n"
								"layout (location = 0) in vec2 position;\n"
								"layout (location = 1) in vec2 texCoord;\n"
								"out vec2 outTexCoord;\n"
								"void main()\n"
								"{\n"
								"	gl_Position = vec4(position, 0.0, 1.0);\n"
								"	outTexCoord = texCoord;\n"
								"}";

constexpr const char* gammaFS =	"#version 460 core\n"
								"out vec4 FragColor;\n"
								"in vec2 outTexCoord;\n"
								"uniform sampler2D scene;\n"
								"void main()\n"
								"{\n"
								"	FragColor = vec4(pow(texture(scene, outTexCoord), vec4(1.0 / 2.2)));\n"
								//"	FragColor = vec4(vec3(1.0 - texture(scene, outTexCoord)), 1.0);\n"
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