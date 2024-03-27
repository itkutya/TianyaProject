#pragma once

#include <cstdint>

namespace ikk
{
	class Window;
	class Time;
	class Event;

	class Scene
	{
	public:
		typedef std::uint32_t SceneID;

		Scene() noexcept;

		Scene(const Scene&) noexcept = default;
		Scene(Scene&) noexcept = default;
		Scene(Scene&&) noexcept = default;

		Scene& operator=(const Scene&) noexcept = default;
		Scene& operator=(Scene&) noexcept = default;
		Scene& operator=(Scene&&) noexcept = default;

		virtual ~Scene() noexcept = default;

		virtual void processEvent(const Event& event) noexcept = 0;
		virtual void update(const Time& dt) noexcept = 0;
		virtual void draw(const Window& window) noexcept = 0;

		[[nodiscard]] virtual const SceneID& getID() const noexcept final;
	protected:
		SceneID m_id;
	};
}