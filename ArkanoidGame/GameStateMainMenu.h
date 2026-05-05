#pragma once

#include "MenuItem.h"
#include "GameStateData.h"

namespace ArkanoidGame
{
	class GameStateMainMenuData : public GameStateData
	{
	private:
		/// Fonts

		sf::Font font;

		/// Texts

		sf::Text title;

		/// Buttons

		// Actual (focused) button
		active it;

		// All window buttons
		std::list<MenuItem<call>> buttons;

	public:
		GameStateMainMenuData() = default;
		~GameStateMainMenuData() = default;

		void init() override;
		void handleWindowEvent(const sf::Event& event) override;
		void draw(sf::RenderWindow& window) override;
		void update(float deltaTime) override;
	};
}