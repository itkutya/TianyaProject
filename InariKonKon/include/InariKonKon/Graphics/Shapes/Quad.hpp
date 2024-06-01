#pragma once

#include <array>

#include "InariKonKon/Graphics/Vertex/Vertex.hpp"
#include "InariKonKon/Graphics/Drawable.hpp"
#include "InariKonKon/Window/Window.hpp"

namespace ikk
{
	template<Dimension D = Dimension::_2D>
	class Quad final : public Drawable<D>
	{
	public:
		Quad(const Color c = Color::White) noexcept;

		Quad(const Quad<D>&) noexcept = default;
		Quad(Quad<D>&&) noexcept = default;

		Quad<D>& operator=(const Quad<D>&) noexcept = default;
		Quad<D>& operator=(Quad<D>&&) noexcept = default;

		~Quad() noexcept = default;

		void draw(const Window& target, const RenderState<D, Projection::Orhto>& state) const noexcept override;
		void draw(const Window& target, const RenderState<D, Projection::Perspective>& state) const noexcept override;

		[[nodiscard]] const std::array<Vertex, 4>& getVertices() const noexcept;
		[[nodiscard]] std::array<Vertex, 4>& getVertices() noexcept;
	private:
		std::array<Vertex, 4> m_vertices
		{
			Vertex({  1.f,  1.f, 0.0f }, Color::White, { 1.f, 1.f }),
			Vertex({  1.f, -1.f, 0.0f }, Color::White, { 1.f, 0.f }),
			Vertex({ -1.f, -1.f, 0.0f }, Color::White, { 0.f, 0.f }),
			Vertex({ -1.f,  1.f, 0.0f }, Color::White, { 0.f, 1.f })
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
	inline Quad<D>::Quad(const Color c) noexcept
	{
		for (Vertex& vertex : this->m_vertices)
			vertex.color = c;

		this->m_VAO.bind();
		this->m_VBO.BufferData(std::span{ this->m_vertices });
		this->m_EBO.BufferData(std::span{ this->m_indices });
		this->m_VAO.setupVertexAttributes();
	}

	template<Dimension D>
	inline void Quad<D>::draw(const Window& target, const RenderState<D, Projection::Orhto>& state) const noexcept
	{
		state.shader->bind();

		if (state.texture)
			state.texture->bind();

		if (state.camera != nullptr)
		{
			if (state.transform)
				state.shader->setMatrix4x4("model", state.transform->getMatrix());
			else
				state.shader->setMatrix4x4("model", this->getTransform().getMatrix());

			state.shader->setMatrix4x4("view", state.camera->getViewMatrix());
			state.shader->setMatrix4x4("projection", state.camera->getProjectionMatrix(2.f, 2.f, -2.f, -2.f));
		}

		this->m_VAO.bind();
		target.draw(Primitive::Triangles, this->m_indices.size(), this->m_EBO.getType());
	}

	template<Dimension D>
	inline void Quad<D>::draw(const Window& target, const RenderState<D, Projection::Perspective>& state) const noexcept
	{
		state.shader->bind();

		if (state.texture)
			state.texture->bind();

		if (state.camera != nullptr)
		{
			mat4x4 model(1.f);
			state.shader->setMatrix4x4("model", model);
			state.shader->setMatrix4x4("view", state.camera->getViewMatrix());
			state.shader->setMatrix4x4("projection", state.camera->getProjectionMatrix(target.getAspectRatio()));
		}

		this->m_VAO.bind();
		target.draw(Primitive::Triangles, this->m_indices.size(), this->m_EBO.getType());
	}

	template<Dimension D>
	inline const std::array<Vertex, 4>& Quad<D>::getVertices() const noexcept
	{
		return this->m_vertices;
	}

	template<Dimension D>
	inline std::array<Vertex, 4>& Quad<D>::getVertices() noexcept
	{
		return this->m_vertices;
	}
}