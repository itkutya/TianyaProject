#include "InariKonKon/InariKonKon.hpp"

//Entity components system -> no -> too much for this scale of game engine
//Entity -> application should keep an eye on them or smthg...

inline static const std::string defaultVS =
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

inline static const std::string defaultFS =
R"(#version 460 core

out vec4 FragColor;

in vec4 outColor;
in vec2 outTexCoord;

layout(binding = 0) uniform sampler2D tex;

void main()
{
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(tex, outTexCoord).r);
	FragColor = vec4(outColor.rgb, 1.0) * sampled;
})";

class TestScene final : public ikk::Scene
{
public:
	TestScene(ikk::Application& app) noexcept : ikk::Scene(app/*, ikk::PostEffects::All*/)
	{
	};

	TestScene(const TestScene&) noexcept = default;
	TestScene(TestScene&&) noexcept = default;

	TestScene& operator=(const TestScene&) noexcept = default;
	TestScene& operator=(TestScene&&) noexcept = default;

	~TestScene() noexcept = default;

	void handleEvents(const ikk::Event& event) noexcept override
	{
		if (event.type == ikk::Event::Type::KeyDown)
		{
			if (event.keyboard.keycode == ikk::Keyboard::KeyCode::A)
				std::printf("A\n");
		}
	};

	void update(const ikk::Time& dt) noexcept override
	{
		//Same problem...
		text.setFont(font);
	};

	void render(const ikk::Window& window) const noexcept override
	{
		window.draw(quad, ikk::RenderState{ .texture = &wall, .camera = &mainCamera });
		window.draw(triangle, ikk::RenderState{ .texture = &wall });
		window.draw(text, ikk::RenderState{ .shader = &textShader, .texture = &font.getTexture(), .camera = &orthoCamera });
	};
private:
	ikk::Quad2D quad{ { 0.f, 0.f, -2.f } };
	ikk::Triangle3D triangle{ { 0.f, 0.f, -5.f }, { 1.f, 1.f }, ikk::Color::Black };
	ikk::Camera<ikk::Projection::Perspective> mainCamera;
	ikk::Texture wall{ "wall.jpg" };
	ikk::Font font{ "Baefont_normal-Regular_V1.ttf" };
	//Fix it... & at least it renders...
	ikk::Text3D text{ u8"Hello World!", { 25.f, 400.f, -5.f }, 1.f, ikk::Color::Red };
	//Only works with ortho camera rn...
	ikk::Camera<ikk::Projection::Ortho> orthoCamera;
	ikk::Shader textShader{ defaultVS.c_str(), defaultFS.c_str() };
};

int main()
{
	try
	{
		ikk::Application app = { u8"日本", ikk::Window::Settings{ .size = { 500, 600 }, .vsync = true, .fullscreen = false } };
		app.getSceneManager().add(TestScene(app));
		app.run(ikk::Color::Cyan);
	}
	catch (...)
	{
		return -1;
	}
	return 0;
}