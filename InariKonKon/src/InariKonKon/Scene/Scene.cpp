#include "InariKonKon/Scene/Scene.hpp"

namespace ikk
{
	namespace priv
	{
		inline static const std::uint32_t getNextUniqueID() noexcept
		{
			static std::uint32_t id = 0ULL;
			return ++id;
		}
	}

	Scene::Scene() noexcept : m_id(priv::getNextUniqueID())
	{
	}

	const Scene::SceneID& Scene::getID() const noexcept
	{
		return this->m_id;
	}
}