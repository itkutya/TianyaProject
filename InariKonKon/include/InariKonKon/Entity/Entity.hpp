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

		const bool operator==(const Entity& other) const noexcept;

		const EntityID& getID() const noexcept;

		//template<EntityComponent C>
		//const std::shared_ptr<C>& get() const noexcept;
		//template<EntityComponent C>
		//std::shared_ptr<C>& get() noexcept;
	private:
		EntityID m_id = 0;
	};

	/*
	template<EntityComponent C>
	const std::shared_ptr<C>& Entity::get() const noexcept
	{
	}

	template<EntityComponent C>
	std::shared_ptr<C>& Entity::get() noexcept
	{
	}
	*/

	namespace priv
	{
		struct EntityHasher
		{
			const std::size_t operator()(const ikk::Entity* entity) const
			{
				return entity->getID();
			}
		};
	}
}