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
		
		typedef std::unordered_map<priv::EntityComponentBase::EntityComponentID, std::shared_ptr<priv::EntityComponentBase>> EntityComponentList;
	public:
		~EntityComponentSystem() noexcept = default;

		template<class C, EntityType T>
		C& add(T* entity) noexcept;

		template<EntityType T>
		[[nodiscard]] EntityComponentList& getComponents(T* entity) noexcept;
		template<class C, EntityType T>
		[[nodiscard]] C& get(T* entity) noexcept;
	private:
		std::unordered_map<Entity*, EntityComponentList, priv::EntityHasher, priv::EntityEqual> m_entities;
	};

	template<class C, EntityType T>
	C& EntityComponentSystem::add(T* entity) noexcept
	{
		EntityComponentList& newEntityComponentList = this->m_entities.emplace(std::make_pair(entity, EntityComponentList{})).first->second;
		return *static_cast<C*>(newEntityComponentList.emplace(std::make_pair(C::ID, std::make_shared<C>())).first->second.get());
	}

	template<EntityType T>
	EntityComponentSystem::EntityComponentList& EntityComponentSystem::getComponents(T* entity) noexcept
	{
		return this->m_entities.at(entity);
	}

	template<class C, EntityType T>
	C& EntityComponentSystem::get(T* entity) noexcept
	{
		return *static_cast<C*>(this->m_entities.at(entity).at(C::ID).get());
	}
}