#pragma once

#include <string_view>

#include "InariKonKon/Graphics/Transform/Transformable.hpp"
#include "InariKonKon/Graphics/Draw/Drawable.hpp"
#include "InariKonKon/Graphics/Vertex/Vertex.hpp"
#include "InariKonKon/Window/Window.hpp"

namespace ikk
{
	template<Dimension D = Dimension::_2D>
	class Text final : public Drawable<D>, public Transformable<D>
	{
	public:
		Text(const std::string_view text) noexcept;

		Text(const Text<D>&) noexcept = default;
		Text(Text<D>&&) noexcept = default;

		Text<D>& operator=(const Text<D>&) noexcept = default;
		Text<D>& operator=(Text<D>&&) noexcept = default;

		~Text() noexcept = default;

		void draw(const Window& window, RenderState<D, Projection::Ortho>& state) const noexcept override;
		void draw(const Window& window, RenderState<D, Projection::Perspective>& state) const noexcept override;
	private:
	};

	using Text3D = Text<Dimension::_3D>;
	using Text2D = Text<Dimension::_2D>;
	using TextGUI = Text<Dimension::_GUI>;

	template<Dimension D>
	Text<D>::Text(const std::string_view text) noexcept
	{
		//this->m_VAO.setup(this->m_VBO, std::span{ this->m_vertices }, this->m_EBO, std::span{ this->m_indices });
	}

	template<Dimension D>
	void Text<D>::draw(const Window& window, RenderState<D, Projection::Ortho>& state) const noexcept
	{
		if (state.transform == nullptr)
			state.transform = &this->getTransform();

		this->preDraw(window, state);
	}

	template<Dimension D>
	void Text<D>::draw(const Window& window, RenderState<D, Projection::Perspective>& state) const noexcept
	{
		if (state.transform == nullptr)
			state.transform = &this->getTransform();

		this->preDraw(window, state, window.getAspectRatio());
	}
}