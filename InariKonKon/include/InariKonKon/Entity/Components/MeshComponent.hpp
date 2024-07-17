#pragma once

#include "InariKonKon/Entity/Components/EntityComponentBase.hpp"

namespace ikk
{
	class Window;

	class MeshComponent : public EntityComponent<1>
	{
	public:
	private:
		void draw() const noexcept {};

		friend class Window;
	};
}