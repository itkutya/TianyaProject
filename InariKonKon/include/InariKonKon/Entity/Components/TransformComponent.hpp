#pragma once

#include "InariKonKon/Entity/Components/EntityComponentBase.hpp"
#include "InariKonKon/Graphics/Transform/Transform.hpp"

namespace ikk
{
	template<Dimension D>
	class TransformComponent : public EntityComponent<0>
	{
	public:
		Transform<D> m_transform{};
	};

	using Transform2DComponent = TransformComponent<Dimension::_2D>;
	using Transform3DComponent = TransformComponent<Dimension::_3D>;
	using TransformUIComponent = TransformComponent<Dimension::_UI>;
}