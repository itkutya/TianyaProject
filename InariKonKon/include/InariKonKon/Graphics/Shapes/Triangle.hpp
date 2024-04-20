#pragma once

#include "InariKonKon/Graphics/Vertex/Vertex.hpp"
#include "InariKonKon/Graphics/Drawable.hpp"

#include "InariKonKon/Graphics/Buffers/VertexBufferObject.hpp"
#include "InariKonKon/Graphics/Buffers/VertexArrayObject.hpp"
#include "InariKonKon/Graphics/Shader/Shader.hpp"

inline static const char* vertexShaderSource =		"#version 460 core\n"
													"layout(location = 0) in vec3 position;\n"
													"layout(location = 1) in vec4 color;\n"
													//"layout(location = 2) in vec2 texCoord;\n"
													"out vec4 outColor;\n"
													//"out vec2 outTexCoord;\n"
													"void main()\n"
													"{\n"
													"	gl_Position = vec4(position, 1.0);\n"
													"	outColor = color;\n"
													//"	outTexCoord = texCoord;\n"
													"}\n\0";

inline static const char* fragmentShaderSource =	"#version 460 core\n"
													"out vec4 FragColor;\n"
													"in vec4 outColor;\n"
													//"in vec2 outTexCoord;\n"
													"void main()\n"
													"{\n"
													"   FragColor = outColor;\n"
													"}\n\0";

namespace ikk
{
	class Triangle final : public Drawable
	{
	public:
		Triangle() noexcept;

		Triangle(const Triangle&) noexcept = default;
		Triangle(Triangle&&) noexcept = default;

		Triangle& operator=(const Triangle&) noexcept = default;
		Triangle& operator=(Triangle&&) noexcept = default;

		~Triangle() noexcept = default;
	private:
		Vertex m_vertices[3]{
								Vertex({ -0.5f, -0.5f, 0.0f }, Color::Red),
								Vertex({  0.5f, -0.5f, 0.0f }, Color::Green),
								Vertex({  0.0f,  0.5f, 0.0f }, Color::Blue)
							};

		priv::VertexBufferObject VBO;
		priv::VertexArrayObject VAO;
		Shader shader{ vertexShaderSource, fragmentShaderSource };

		void draw(const Window& target) noexcept override;
	};
}