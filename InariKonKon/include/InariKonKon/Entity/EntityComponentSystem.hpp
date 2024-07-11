#pragma once

#include <unordered_map>
#include <unordered_set>
#include <memory>

#include "InariKonKon/Entity/Components/EntityComponentBase.hpp"
#include "InariKonKon/Utility/Singleton.hpp"
#include "InariKonKon/Utility/TypeDefs.hpp"
#include "InariKonKon/Entity/Entity.hpp"

namespace ikk
{
	class EntityComponentSystem final : public Singleton<EntityComponentSystem>
	{
		friend Singleton<EntityComponentSystem>;
		EntityComponentSystem() noexcept = default;
		typedef std::unordered_set<std::shared_ptr<EntityComponentBase>, priv::EntityComponentHasher> EntityComponentList;
	public:
		~EntityComponentSystem() noexcept = default;

		template<EntityComponent C, EntityType T>
		C& add(T* entity) noexcept;

		//TODO:
		/*
		template<EntityComponent C, EntityType T>
		const C& get(T* entity) const noexcept;
		template<EntityComponent C, EntityType T>
		C& get(T* entity) noexcept;
		*/
	private:
		std::unordered_map<Entity*, EntityComponentList, priv::EntityHasher> m_entities;
	};

	template<EntityComponent C, EntityType T>
	C& EntityComponentSystem::add(T* entity) noexcept
	{
		EntityComponentList& newEntityComponentList = this->m_entities.emplace(std::make_pair(entity, EntityComponentList{})).first->second;
		return *static_cast<C*>(newEntityComponentList.emplace(std::make_shared<C>()).first->get());
	}
}