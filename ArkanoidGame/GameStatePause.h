#pragma once

#include "MenuItem.h"
#include "GameStateData.h"

namespace ArkanoidGame
{
	class GameStatePauseData : public GameStateData
	{
	private:
		sf::Clock delayClock;
		bool isWaiting = false;
		const float delayTime = 3.0f;
		const sf::String timerText = "Return to the game in ";

		/// Fonts

		sf::Font font;

		/// Texts

		sf::Text title;
		sf::Text timer;

		/// Buttons

		// Actual (focused) button
		active it;

		// All window buttons
		std::list<MenuItem<call>> buttons;

	public:
		GameStatePauseData() = default;
		~GameStatePauseData() = default;

		void init() override;
		void handleWindowEvent(const sf::Event& event) override;
		void draw(sf::RenderWindow& window) override;
		void update(float deltaTime) override;
	};
}