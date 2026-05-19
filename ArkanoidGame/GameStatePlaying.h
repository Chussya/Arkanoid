#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>

#include "Brick.h"
#include "Shell.h"
#include "Platform.h"
#include "IObservable.h"
#include "BrickFactory.h"
#include "LevelManager.h"
#include "GameStateData.h"

namespace ArkanoidGame
{
	class Game;

	class GameStatePlayingData : public GameStateData, public IObserver, public std::enable_shared_from_this<GameStatePlayingData>
	{
	private:
		// State data

		int score{ 0 };
		float mouseMoveX{ 0.f };

		// Game objects

		std::vector<std::shared_ptr<GameObject>> gameObjects;
		std::vector<std::shared_ptr<Brick>> bricks;

		std::unordered_map<BrickType, std::unique_ptr<BrickFactory>> brickFactories;
		int breackableBricksCount{ 0 };

		// Level

		LevelManager levelManager;
		int currentLevel{ 1 };

		/// Resources
		// Font

		sf::Font font;

		// Text

		sf::Text scoreText;
		sf::Text pauseNote;

		// Sounds

		sf::Sound soundHit;

	public:
		GameStatePlayingData();
		~GameStatePlayingData();

		// GameStateData methods

		void init() override;
		void handleWindowEvent(const sf::Event& event) override;
		void draw(sf::RenderWindow& window) override;
		void update(float deltaTime) override;

		// Other

		void loadNextLevel();
		void createLevel();

		// Inherited via IObserver

		void Notify(std::shared_ptr<IObservable> observable) override;
	};
}