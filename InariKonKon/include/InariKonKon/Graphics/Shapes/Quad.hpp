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

		Quad(const Quad&) noexcept = default;
		Quad(Quad&&) noexcept = default;

		Quad& operator=(const Quad&) noexcept = default;
		Quad& operator=(Quad&&) noexcept = default;

		~Quad() noexcept = default;

		void draw(const Window& target, const RenderState<D, Projection::Orhto>& state) const noexcept override;
		void draw(const Window& target, const RenderState<D, Projection::Perspective>& state) const noexcept override;
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
			mat4x4 model(1.f);
			state.shader->setMatrix4x4("model", model);
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
}