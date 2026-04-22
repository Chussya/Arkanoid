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
		GameStatePlayingData() = default;

		void handleWindowEvent(const sf::Event event);

		void init();
		void draw(sf::RenderWindow& window);
		void update(float deltaTime);
		void shutdown();
	};
}