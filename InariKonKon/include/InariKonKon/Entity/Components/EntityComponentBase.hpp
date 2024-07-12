#pragma once

#include <cstddef>
#include <memory>

namespace ikk
{
	class EntityComponentBase
	{
	public:
		typedef std::uint32_t EntityComponentID;

		EntityComponentBase(const EntityComponentID id) noexcept;

		EntityComponentBase(const EntityComponentBase&) noexcept = default;
		EntityComponentBase(EntityComponentBase&&) noexcept = default;

		virtual EntityComponentBase& operator=(const EntityComponentBase&) noexcept = default;
		virtual EntityComponentBase& operator=(EntityComponentBase&&) noexcept = default;

		virtual ~EntityComponentBase() noexcept = default;

		const EntityComponentID& getID() const noexcept;
	private:
		EntityComponentID m_id = 0;
	};

	namespace priv
	{
		struct EntityComponentHasher
		{
			const std::size_t operator()(const std::shared_ptr<EntityComponentBase>& component) const
			{
				return component->getID();
			}
		};

		struct EntityComponentEqual
		{
			const bool operator()(const std::shared_ptr<EntityComponentBase>& lhs, const std::shared_ptr<EntityComponentBase>& rhs) const
			{
				return lhs->getID() == rhs->getID();
			}
		};
	}
}