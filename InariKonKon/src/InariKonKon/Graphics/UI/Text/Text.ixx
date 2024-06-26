module;

#include "InariKonKon/Graphics/OpenGL.hpp"

export module Text;

import <string_view>;

export import Transformable;
export import Drawable;
export import Vertex;

import ElementBufferObject;
import VertexBufferObject;
import VertexArrayObject;
import Context;
import Window;

export namespace ikk
{
	template<Dimension D = Dimension::_2D>
	class Text final : public Drawable<D>, public Transformable<D>
	{
	public:
		Text() noexcept;

		Text(const Text<D>&) noexcept = default;
		Text(Text<D>&&) noexcept = default;

		Text<D>& operator=(const Text<D>&) noexcept = default;
		Text<D>& operator=(Text<D>&&) noexcept = default;

		~Text() noexcept = default;

		void draw(const Window& target, RenderState<D, Projection::Ortho>& state) const noexcept override;
		void draw(const Window& target, RenderState<D, Projection::Perspective>& state) const noexcept override;
	private:
	};

	template<Dimension D>
	Text<D>::Text() noexcept
	{
	}

	template<Dimension D>
	void Text<D>::draw(const Window& target, RenderState<D, Projection::Ortho>& state) const noexcept
	{
	}

	template<Dimension D>
	void Text<D>::draw(const Window& target, RenderState<D, Projection::Perspective>& state) const noexcept
	{
	}
}