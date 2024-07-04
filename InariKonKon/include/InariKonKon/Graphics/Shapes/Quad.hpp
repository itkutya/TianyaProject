#pragma once

#include <array>

#include "InariKonKon/Graphics/Transform/Transformable.hpp"
#include "InariKonKon/Graphics/Draw/Drawable.hpp"
#include "InariKonKon/Graphics/Vertex/Vertex.hpp"
#include "InariKonKon/Utility/Math/Rect.hpp"
#include "InariKonKon/Window/Window.hpp"

namespace ikk
{
	template<Dimension D = Dimension::_2D>
	class Quad final : public Drawable<D>, public Transformable<D>
	{
	public:
		Quad(const Color color = Color::White, const FloatRect textureRect = { 0.f, 0.f, 1.f, 1.f }) noexcept;

		Quad(const Quad<D>&) noexcept = default;
		Quad(Quad<D>&&) noexcept = default;

		Quad<D>& operator=(const Quad<D>&) noexcept = default;
		Quad<D>& operator=(Quad<D>&&) noexcept = default;

		~Quad() noexcept = default;

		void draw(const Window& window, RenderState<D, Projection::Ortho>& state) const noexcept override;
		void draw(const Window& window, RenderState<D, Projection::Perspective>& state) const noexcept override;

		[[nodiscard]] const std::array<Vertex, 4>& getVertices() const noexcept;
		[[nodiscard]] std::array<Vertex, 4>& getVertices() noexcept;
	private:
		std::array<Vertex, 4> m_vertices =
		{
			Vertex({ -1.f, -1.f, 0.f }, Color::White, { 0.f, 1.f }),
			Vertex({ -1.f,  1.f, 0.f }, Color::White, { 0.f, 0.f }),
			Vertex({  1.f, -1.f, 0.f }, Color::White, { 1.f, 1.f }),
			Vertex({  1.f,  1.f, 0.f }, Color::White, { 1.f, 0.f })
		};

		std::array<std::uint8_t, 6> m_indices
		{
			0, 1, 2,
			1, 2, 3
		};
	};

	using Quad3D = Quad<Dimension::_3D>;
	using Quad2D = Quad<Dimension::_2D>;
	using QuadGUI = Quad<Dimension::_GUI>;

	template<Dimension D>
	Quad<D>::Quad(const Color color, const FloatRect textureRect) noexcept
	{
		for (Vertex& vertex : this->m_vertices)
			vertex.color = color;

		this->m_vertices[0].texCoord = { textureRect.left, textureRect.bottom };
		this->m_vertices[1].texCoord = { textureRect.left, textureRect.top };
		this->m_vertices[2].texCoord = { textureRect.right, textureRect.bottom };
		this->m_vertices[3].texCoord = { textureRect.right, textureRect.top };

		this->m_VAO.setup(this->m_VBO, std::span{ this->m_vertices }, this->m_EBO, std::span{ this->m_indices });
	}

	template<Dimension D>
	void Quad<D>::draw(const Window& window, RenderState<D, Projection::Ortho>& state) const noexcept
	{
		if (state.transform == nullptr)
			state.transform = &this->getTransform();

		this->preDraw(window, state, { -(float)window.getSize().x / 2.f, -(float)window.getSize().y / 2.f, (float)window.getSize().x / 2.f, (float)window.getSize().y / 2.f });
		gl->DrawElements(GL_TRIANGLES, static_cast<GLsizei>(this->m_indices.size()), this->m_EBO.getType(), 0);
	}

	template<Dimension D>
	void Quad<D>::draw(const Window& window, RenderState<D, Projection::Perspective>& state) const noexcept
	{
		if (state.transform == nullptr)
			state.transform = &this->getTransform();

		this->preDraw(window, state, window.getAspectRatio());
		gl->DrawElements(GL_TRIANGLES, static_cast<GLsizei>(this->m_indices.size()), this->m_EBO.getType(), 0);
	}

	template<Dimension D>
	const std::array<Vertex, 4>& Quad<D>::getVertices() const noexcept
	{
		return this->m_vertices;
	}

	template<Dimension D>
	std::array<Vertex, 4>& Quad<D>::getVertices() noexcept
	{
		return this->m_vertices;
	}
}