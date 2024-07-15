#pragma once

#include <unordered_map>
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

		typedef std::shared_ptr<priv::EntityComponentBase> EntityComponent;
		typedef std::unordered_map<Entity*, EntityComponent, priv::EntityHasher, priv::EntityEqual> EntityListWithComponents;
	public:
		~EntityComponentSystem() noexcept = default;

		template<EntityComponentType C>
		C& add(Entity* entity) noexcept;

		template<EntityComponentType C>
		[[nodiscard]] C& get(Entity* entity) noexcept;
		template<EntityComponentType C>
		[[nodiscard]] const C& get(Entity* entity) const noexcept;
		template<EntityComponentType C>
		[[nodiscard]] const bool contains(Entity* entity) const noexcept;
	private:
		std::unordered_map<priv::EntityComponentBase::EntityComponentID, EntityListWithComponents> m_entities;
	};

	template<EntityComponentType C>
	C& EntityComponentSystem::add(Entity* entity) noexcept
	{
		const auto& inserted = this->m_entities.try_emplace(C::ID, EntityListWithComponents{ { entity, std::make_shared<C>() } });
		if (!inserted.second)
			inserted.first->second.try_emplace(entity, std::make_shared<C>());
		return *static_cast<C*>(inserted.first->second.at(entity).get());
	}

	template<EntityComponentType C>
	C& EntityComponentSystem::get(Entity* entity) noexcept
	{
		return *static_cast<C*>(this->m_entities.at(C::ID).at(entity).get());
	}

	template<EntityComponentType C>
	const C& EntityComponentSystem::get(Entity* entity) const noexcept
	{
		return *static_cast<C*>(this->m_entities.at(C::ID).at(entity).get());
	}

	template<EntityComponentType C>
	const bool EntityComponentSystem::contains(Entity* entity) const noexcept
	{
		if (!this->m_entities.contains(C::ID))
			return false;
		return this->m_entities.at(C::ID).contains(entity);
	}
}