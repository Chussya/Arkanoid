#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//#include "Record.h"
#include "GameSettings.h"
#include "GameState.h"

namespace ArkanoidGame
{
	class Game
	{
	private:
		// Global data
		int* ptrPlayerScores{ nullptr };

		std::vector<GameState> gameStateStack;
		EGameStateChangeType gameStateChangeType = EGameStateChangeType::None;
		EGameStateType pendingGameStateType = EGameStateType::None;
		bool pendingGameStateIsExclusivelyVisible = false;

		std::unordered_map<std::string, int> records;

	public:
		Game();
		~Game();

		void handleWindowEvents(sf::RenderWindow& window);
		bool update(float deltaTime); // Return false if game should be closed
		void draw(sf::RenderWindow& window);

		// Add new game state on top of the stack
		void pushGameState(EGameStateType stateType, bool isExclusivelyVisible);

		// Remove current game state from the stack
		void popGameState();

		// Remove all game states from the stack and add new one
		void switchGameState(EGameStateType newState);
	};
}