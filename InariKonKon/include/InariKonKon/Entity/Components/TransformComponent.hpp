#pragma once

#include "InariKonKon/Entity/Components/EntityComponentBase.hpp"
#include "InariKonKon/Graphics/Transform/Transform.hpp"

namespace ikk
{
	class TransformComponent : public EntityComponent<1>
	{
	public:
		Transform<Dimension::_2D> m_transform{};
	};
}