#pragma once

#include <array>

#include "InariKonKon/Graphics/Transform/Transformable.hpp"
#include "InariKonKon/Graphics/Vertex/Vertex.hpp"
#include "InariKonKon/Graphics/Draw/Drawable.hpp"
#include "InariKonKon/Graphics/OpenGL/OpenGL.hpp"
#include "InariKonKon/Window/Window.hpp"

namespace ikk
{
	template<Dimension D = Dimension::_2D>
	class Quad final : public Drawable<D>, public Transformable<D>
	{
	public:
		Quad() noexcept;

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
			Vertex({  1.f,  1.f, -1.f }, Color::White, { 1.f, 1.f }),
			Vertex({  1.f, -1.f, -1.f }, Color::White, { 1.f, 0.f }),
			Vertex({ -1.f, -1.f, -1.f }, Color::White, { 0.f, 0.f }),
			Vertex({ -1.f,  1.f, -1.f }, Color::White, { 0.f, 1.f })
		};

		std::array<std::uint8_t, 6> m_indices
		{
			0, 1, 3,
			1, 2, 3
		};
	};

	using Quad3D = Quad<Dimension::_3D>;
	using Quad2D = Quad<Dimension::_2D>;
	using QuadGUI = Quad<Dimension::_GUI>;

	template<Dimension D>
	Quad<D>::Quad() noexcept
	{
		//this->m_VAO.setup(this->m_VBO, std::span{ this->m_vertices }, this->m_EBO, std::span{ this->m_indices });
	}

	template<Dimension D>
	void Quad<D>::draw(const Window& window, RenderState<D, Projection::Ortho>& state) const noexcept
	{
		if (state.transform == nullptr)
			state.transform = &this->getTransform();

		this->preDraw(window, state);
		//TODO:
		gl->DrawElements(GL_TRIANGLES, static_cast<GLsizei>(this->m_indices.size()), GL_UNSIGNED_BYTE, 0);
	}

	template<Dimension D>
	void Quad<D>::draw(const Window& window, RenderState<D, Projection::Perspective>& state) const noexcept
	{
		if (state.transform == nullptr)
			state.transform = &this->getTransform();

		this->preDraw(window, state, window.getAspectRatio());
		//TODO:
		gl->DrawElements(GL_TRIANGLES, static_cast<GLsizei>(this->m_indices.size()), GL_UNSIGNED_BYTE, 0);
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