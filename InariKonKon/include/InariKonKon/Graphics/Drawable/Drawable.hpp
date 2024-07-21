#pragma once

#include "InariKonKon/Graphics/RenderState/RenderState.hpp"
#include "InariKonKon/Transform/Transform.hpp"

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
		void predraw(const RenderState<P>& state, const Transform* transform, const FloatRect viewRect) const noexcept;
		template<Projection P>
		void postdraw(const RenderState<P>& state) const noexcept;
	};

	template<Projection P>
	void Drawable::predraw(const RenderState<P>& state, const Transform* transform, const FloatRect viewRect) const noexcept
	{
		state.shader->bind();

		if (state.texture)
			state.texture->bind();

		if (transform)
			state.shader->setMatrix4x4("model", transform->getMatrix());

		if constexpr (P == Projection::Ortho)
			state.shader->setCamera(*state.camera, viewRect);
		else if constexpr (P == Projection::Perspective)
			state.shader->setCamera(*state.camera, viewRect.right / viewRect.top);
	}

	template<Projection P>
	void Drawable::postdraw(const RenderState<P>& state) const noexcept
	{
		state.shader->unbind();

		if (state.texture)
			state.texture->unbind();
	}
}