#pragma once

#include <unordered_map>
#include <vector>
#include <memory>

#include "InariKonKon/Entity/Components/EntityComponentBase.hpp"
#include "InariKonKon/Utility/Singleton.hpp"
#include "InariKonKon/Utility/TypeDefs.hpp"

namespace ikk
{
	class EntityComponentSystem final : public Singleton<EntityComponentSystem>
	{
		friend Singleton<EntityComponentSystem>;
		EntityComponentSystem() noexcept = default;

		typedef std::shared_ptr<priv::EntityComponentBase> EntityComponent;
		typedef std::unordered_map<Entity*, EntityComponent> EntityListWithComponents;
	public:
		~EntityComponentSystem() noexcept = default;

		template<EntityComponentType C, EntityType T>
		C& add(T* entity) noexcept;

		//template<EntityType T>
		//[[nodiscard]] EntityComponentList& getComponents(T* entity) noexcept;
		template<EntityComponentType C, EntityType T>
		[[nodiscard]] C& get(T* entity) noexcept;
		template<EntityComponentType C, EntityType T>
		[[nodiscard]] const C& get(T* entity) const noexcept;
	private:
		std::unordered_map<priv::EntityComponentBase::EntityComponentID, EntityListWithComponents> m_entities;
	};

	template<EntityComponentType C, EntityType T>
	C& EntityComponentSystem::add(T* entity) noexcept
	{
		const auto& inserted = this->m_entities.try_emplace(C::ID, EntityListWithComponents{ { entity, std::make_shared<C>() } });
		if (!inserted.second)
			inserted.first->second.emplace(std::make_pair<Entity*, EntityComponent>(entity, std::make_shared<C>()));
		return *static_cast<C*>(inserted.first->second.at(entity).get());
	}

	template<EntityComponentType C, EntityType T>
	C& EntityComponentSystem::get(T* entity) noexcept
	{
		return *static_cast<C*>(this->m_entities.at(C::ID).at(entity).get());
	}

	template<EntityComponentType C, EntityType T>
	const C& EntityComponentSystem::get(T* entity) const noexcept
	{
		return *static_cast<C*>(this->m_entities.at(C::ID).at(entity).get());
	}
}