#pragma once

#include <cstddef>
#include <memory>

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

			virtual const EntityComponentID& getID() const noexcept final;
		private:
			EntityComponentID m_id;
		};

		static const priv::EntityComponentBase::EntityComponentID generateUniqueID() noexcept;
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

		inline static priv::EntityComponentBase::EntityComponentID ID = ID;
	};

	template<priv::EntityComponentBase::EntityComponentID ID>
	EntityComponent<ID>::EntityComponent() noexcept : priv::EntityComponentBase(ID)
	{
	}
}

//#define EntityComponent EntityComponent<ikk::priv::generateUniqueID()>