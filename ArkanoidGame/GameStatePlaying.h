#pragma once

#include <SFML/Graphics.hpp>

#include "Shell.h"
#include "Platform.h"

namespace ArkanoidGame
{
	class Game;

	class GameStatePlayingData
	{
	private:
		// State data

		float mouseMoveX{ 0.f };

		// Game objects

		Platform player;
		Shell shell;

		// Resources

		//sf::Texture appleTexture;

		// Font

		sf::Font font;

		// Text

		sf::Text scoreText;
		sf::Text pauseNote;

	public:
		GameStatePlayingData();

		void HandleGameStateWindowEvent(Game& game, const sf::Event event);

		void InitGameState(Game& game);
		void DrawGameState(Game& game, sf::RenderWindow& window);
		void UpdateGameState(Game& game, float deltaTime);
		void ShutdownGameState(Game& game);
	};
}