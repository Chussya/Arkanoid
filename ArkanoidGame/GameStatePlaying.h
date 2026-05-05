#pragma once

#include <SFML/Graphics.hpp>

#include "Brick.h"
#include "Shell.h"
#include "Platform.h"
#include "GameStateData.h"

namespace ArkanoidGame
{
	class Game;

	class GameStatePlayingData : public GameStateData, public std::enable_shared_from_this<GameStatePlayingData>
	{
	private:
		// State data

		float mouseMoveX{ 0.f };

		// Game objects

		std::vector<std::shared_ptr<GameObject>> gameObjects;
		std::vector<std::shared_ptr<Brick>> bricks;

		/// Resources

		// Font

		sf::Font font;

		// Text

		sf::Text scoreText;
		sf::Text pauseNote;

	public:
		~GameStatePlayingData() = default;

		// GameStateData methods

		void init() override;
		void handleWindowEvent(const sf::Event& event) override;
		void draw(sf::RenderWindow& window) override;
		void update(float deltaTime) override;

		// Other

		void createBlocks(const int count);
	};
}