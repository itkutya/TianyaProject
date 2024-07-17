#pragma once

#include <unordered_map>
#include <memory>

#include "InariKonKon/Entity/Components/EntityComponentBase.hpp"
#include "InariKonKon/Utility/Singleton.hpp"
#include "InariKonKon/Utility/TypeDefs.hpp"

namespace ikk
{
	class Entity;
	namespace priv
	{
		struct EntityHasher;
		struct EntityEqual;
	}

	class EntityComponentSystem final : public Singleton<EntityComponentSystem>
	{
		friend Singleton<EntityComponentSystem>;
		EntityComponentSystem() noexcept = default;

		typedef std::shared_ptr<priv::EntityComponentBase> EntityComponent;
		typedef std::unordered_map<const Entity*, EntityComponent, priv::EntityHasher, priv::EntityEqual> EntityListWithComponents;
	public:
		~EntityComponentSystem() noexcept = default;

		template<EntityComponentType C>
		C& add(const Entity* const entity) noexcept;

		template<EntityComponentType C>
		[[nodiscard]] C& get(const Entity* const entity) noexcept;
		template<EntityComponentType C>
		[[nodiscard]] const C& get(const Entity* const entity) const noexcept;
		template<EntityComponentType C>
		[[nodiscard]] const bool contains(const Entity* const entity) const noexcept;
	private:
		std::unordered_map<priv::EntityComponentBase::EntityComponentID, EntityListWithComponents> m_entities;
	};

	template<EntityComponentType C>
	C& EntityComponentSystem::add(const Entity* const entity) noexcept
	{
		const auto& inserted = this->m_entities.try_emplace(C::ID, EntityListWithComponents{ { entity, std::make_shared<C>() } });
		if (!inserted.second)
			inserted.first->second.try_emplace(entity, std::make_shared<C>());
		return *static_cast<C*>(inserted.first->second.at(entity).get());
	}

	template<EntityComponentType C>
	C& EntityComponentSystem::get(const Entity* const entity) noexcept
	{
		return *static_cast<C*>(this->m_entities.at(C::ID).at(entity).get());
	}

	template<EntityComponentType C>
	const C& EntityComponentSystem::get(const Entity* const entity) const noexcept
	{
		return *static_cast<C*>(this->m_entities.at(C::ID).at(entity).get());
	}

	template<EntityComponentType C>
	const bool EntityComponentSystem::contains(const Entity* const entity) const noexcept
	{
		if (!this->m_entities.contains(C::ID))
			return false;
		return this->m_entities.at(C::ID).contains(entity);
	}
}