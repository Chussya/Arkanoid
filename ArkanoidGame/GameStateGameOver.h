#pragma once

#include "MenuItem.h"
#include "GameStateData.h"

namespace ArkanoidGame
{
	class GameStateGameOverData : public GameStateData
	{
	private:
		const int maxRecords{ 5 };

		/// Font

		sf::Font font;
		sf::Font recordsFont;

		/// Text

		sf::Text leaderBoardText;
		sf::Text gameOverText;

		/// Buttons

		// Actual (focused) button
		active it;

		// All window buttons
		std::list<MenuItem<call>> buttons;

	public:
		GameStateGameOverData() = default;
		~GameStateGameOverData() = default;

		void init() override;
		void handleWindowEvent(const sf::Event& event) override;
		void draw(sf::RenderWindow& window) override;
		void update(float deltaTime) override;
		
		void popUpNewRecords();
	};
}
