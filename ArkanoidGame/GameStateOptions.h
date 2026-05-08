#pragma once

#include "MenuItem.h"
#include "GameStateData.h"

namespace ArkanoidGame
{
	class GameStateOptionsData : public GameStateData
	{
	private:
		/// Fonts

		sf::Font font;

		/// Texts

		sf::Text title;

		/// Buttons

		// Actual (focused) button
		activeRow it;

		// All window buttons
		std::list<std::pair<MenuItem<call>, sf::RectangleShape>> buttons;

	public:
		GameStateOptionsData() = default;
		~GameStateOptionsData() = default;

		void init() override;
		void handleWindowEvent(const sf::Event& event) override;
		void draw(sf::RenderWindow& window) override;
		void update(float deltaTime) override;
	};
}