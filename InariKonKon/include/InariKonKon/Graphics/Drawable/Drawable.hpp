#pragma once

#include "InariKonKon/Graphics/RenderState/RenderState.hpp"

namespace ikk
{
	class Window;

	class Drawable
	{
	public:
		Drawable() noexcept = default;

		Drawable(const Drawable&) noexcept = default;
		Drawable(Drawable&&) noexcept = default;

		Drawable& operator=(const Drawable&) noexcept = default;
		Drawable& operator=(Drawable&&) noexcept = default;

		~Drawable() noexcept = default;
	protected:
		virtual void draw() const noexcept = 0;
	private:
		friend class Window;
		template<Projection P>
		void predraw(const RenderState<P>& state) const noexcept;
		template<Projection P>
		void postdraw(const RenderState<P>& state) const noexcept;
	};

	template<Projection P>
	void Drawable::predraw(const RenderState<P>& state) const noexcept
	{
		state.shader->bind();

		if (state.texture)
			state.texture->bind();

		//state.shader->setMatrix4x4("model", {});
		if constexpr (P == Projection::Ortho)
			state.shader->setCamera(*state.camera, FloatRect{});
		else if constexpr (P == Projection::Perspective)
			state.shader->setCamera(*state.camera, 1.f);
	}

	template<Projection P>
	void Drawable::postdraw(const RenderState<P>& state) const noexcept
	{
		state.shader->unbind();

		if (state.texture)
			state.texture->unbind();
	}
}