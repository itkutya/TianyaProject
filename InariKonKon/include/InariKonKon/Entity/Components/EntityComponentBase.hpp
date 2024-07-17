#pragma once

#include <string_view>
#include <cstdint>

namespace ikk
{
	namespace priv
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
			EntityComponentID m_id;
		};
	}

	template<priv::EntityComponentBase::EntityComponentID ID>
	class EntityComponent : public priv::EntityComponentBase
	{
	public:
		EntityComponent() noexcept;

		EntityComponent(const EntityComponent&) noexcept = default;
		EntityComponent(EntityComponent&&) noexcept = default;

		virtual EntityComponent& operator=(const EntityComponent&) noexcept = default;
		virtual EntityComponent& operator=(EntityComponent&&) noexcept = default;

		virtual ~EntityComponent() noexcept = default;

		inline constexpr static priv::EntityComponentBase::EntityComponentID ID = ID;
	};

	template<priv::EntityComponentBase::EntityComponentID ID>
	EntityComponent<ID>::EntityComponent() noexcept : EntityComponentBase(ID)
	{
	}
}