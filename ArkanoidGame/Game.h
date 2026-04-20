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

		sf::Music music;

		GameSettings gameSettings;
		std::unordered_map<std::string, int> records;

	public:
		Game();
		~Game();

		GameSettings getGameSettigns();

		void HandleWindowEvents(sf::RenderWindow& window);
		bool UpdateGame(float deltaTime); // Return false if game should be closed
		void DrawGame(sf::RenderWindow& window);

		// Add new game state on top of the stack
		void PushGameState(EGameStateType stateType, bool isExclusivelyVisible);

		// Remove current game state from the stack
		void PopGameState();

		// Remove all game states from the stack and add new one
		void SwitchGameState(EGameStateType newState);
	};
}