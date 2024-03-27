#pragma once

#include "InariKonKon/Application/Application.hpp"

class Menu : public ikk::Scene
{
public:
	Menu(ikk::Application& app) noexcept;

	Menu(const Menu&) noexcept = default;
	Menu(Menu&) noexcept = default;
	Menu(Menu&&) noexcept = default;

	Menu& operator=(const Menu&) noexcept = default;
	Menu& operator=(Menu&) noexcept = default;
	Menu& operator=(Menu&&) noexcept = default;

	virtual ~Menu() noexcept = default;

	void processEvent(const ikk::Event& event) noexcept override;
	void update(const ikk::Time& dt) noexcept override;
	void draw(const ikk::Window& window) noexcept override;
private:
};