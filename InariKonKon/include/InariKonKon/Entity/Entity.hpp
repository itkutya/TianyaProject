#pragma once

#include <cstdint>
#include <memory>

#include "InariKonKon/Utility/TypeDefs.hpp"

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

		//[[nodiscard]] EntityComponentList& getComponents() noexcept;
		//template<EntityComponent C>
		//[[nodiscard]] C& get() noexcept;
	private:
		EntityID m_id = 0;
	};
	/*
	template<EntityComponent C>
	C& Entity::get() noexcept
	{
		//return 
	}
	*/
	namespace priv
	{
		struct EntityHasher
		{
			const std::size_t operator()(const Entity* entity) const
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