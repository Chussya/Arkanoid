#pragma once

#include <SFML/Graphics.hpp>

#include "Shell.h"
#include "Platform.h"
#include "GameStateData.h"

namespace ArkanoidGame
{
	class Game;

	class GameStatePlayingData : public GameStateData
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
		~GameStatePlayingData() = default;

		void init() override;
		void handleWindowEvent(const sf::Event& event) override;
		void draw(sf::RenderWindow& window) override;
		void update(float deltaTime) override;
	};
}