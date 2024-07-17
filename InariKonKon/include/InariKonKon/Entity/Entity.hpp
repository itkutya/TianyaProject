#pragma once

#include <cstdint>
#include <cassert>

#include "InariKonKon/Entity/EntityComponentSystem.hpp"

namespace ikk
{
	class Entity
	{
	public:
		typedef std::uint32_t EntityID;

		Entity() noexcept;

		Entity(const Entity&) noexcept = default;
		Entity(Entity&&) noexcept = default;

		virtual Entity& operator=(const Entity&) noexcept = default;
		virtual Entity& operator=(Entity&&) noexcept = default;

		virtual ~Entity() noexcept = default;
		
		const EntityID& getID() const noexcept;

		template<EntityComponentType C>
		[[nodiscard]] C& get() noexcept;
		template<EntityComponentType C>
		[[nodiscard]] const C& get() const noexcept;
		template<EntityComponentType C>
		[[nodiscard]] const bool contains() const noexcept;
	private:
		EntityID m_id = 0;

		friend class MeshComponent;
		virtual void draw() const noexcept { assert(false && "Draw is called on an entity that has no override for it's draw function!"); };
	};

	template<EntityComponentType C>
	C& Entity::get() noexcept
	{
		return ikk::EntityComponentSystem::getInstance().get<C>(this);
	}

	template<EntityComponentType C>
	const C& Entity::get() const noexcept
	{
		return ikk::EntityComponentSystem::getInstance().get<C>(this);
	}

	template<EntityComponentType C>
	const bool Entity::contains() const noexcept
	{
		return ikk::EntityComponentSystem::getInstance().contains<C>(this);
	}

	namespace priv
	{
		struct EntityHasher
		{
			const std::size_t operator()(const ikk::Entity* entity) const
			{
				return entity->getID();
			}
		};

		struct EntityEqual
		{
			const bool operator()(const Entity* lhs, const Entity* rhs) const
			{
				return lhs->getID() == rhs->getID();
			}
		};
	}
}