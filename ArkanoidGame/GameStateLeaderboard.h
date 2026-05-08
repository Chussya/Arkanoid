#pragma once

#include "GameStateData.h"

namespace ArkanoidGame
{
	class GameStateLeaderboardData : public GameStateData
	{
	private:
		const int maxRecords{ 10 };

		/// Fonts

		sf::Font font;
		sf::Font recordsFont;

		/// Texts

		sf::Text title;
		sf::Text leaderBoardText;

	public:
		GameStateLeaderboardData() = default;
		~GameStateLeaderboardData() = default;

		void init() override;
		void handleWindowEvent(const sf::Event& event) override;
		void draw(sf::RenderWindow& window) override;
		void update(float deltaTime) override;
	};
}
