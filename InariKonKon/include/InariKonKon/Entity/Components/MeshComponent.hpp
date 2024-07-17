#pragma once

#include "InariKonKon/Entity/Components/EntityComponentBase.hpp"
#include "InariKonKon/Entity/Components/TransformComponent.hpp"
#include "InariKonKon/Graphics/RenderState/RenderState.hpp"
#include "InariKonKon/Entity/Entity.hpp"

namespace ikk
{
	class Window;

	class MeshComponent : public EntityComponent<1>
	{
	public:
	private:
		template<Projection P = Projection::None>
		void draw(const Entity* const entity, const RenderState<P>& state = {}) const noexcept;

		friend class Window;
	};

	template<Projection P>
	void MeshComponent::draw(const Entity* const entity, const RenderState<P>& state) const noexcept
	{
		state.shader->bind();

		if (state.texture)
			state.texture->bind();

		if (state.camera != nullptr)
		{
			if (entity->contains<TransformComponent>())
				state.shader->setMatrix4x4("model", entity->get<TransformComponent>().getMatrix());
			if constexpr (P == Projection::Perspective)
				state.shader->setCamera(*state.camera, state.view.right / state.view.top);
			else if constexpr (P == Projection::Ortho)
				state.shader->setCamera(*state.camera, state.view);
		}

		entity->draw();

		if (state.texture)
			state.texture->unbind();

		if (state.shader)
			state.shader->unbind();
	}
}