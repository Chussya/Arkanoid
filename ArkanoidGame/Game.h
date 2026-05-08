#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Record.h"
#include "GameState.h"
#include "GameSettings.h"
#include "AudioManager.h"

namespace ArkanoidGame
{
	class Game
	{
	private:
		std::vector<GameState> gameStateStack;
		EGameStateChangeType gameStateChangeType = EGameStateChangeType::None;
		EGameStateType pendingGameStateType = EGameStateType::None;
		bool pendingGameStateIsExclusivelyVisible = false;

		Record playerRecord;
		RecordsMap records;

		AudioManager audio;

	public:
		Game();
		~Game();

		// Setters

		void setPlayerRecord(Record record);

		// Getters

		Record getPlayerRecord();
		RecordsMap getRecords();
		AudioManager& getAudio();

		// Records logic

		RecordsVector getSortedRecords();
		void updateRecords(Record record);
		void restartPlayerScore();

		// Common methods

		void handleWindowEvents(sf::RenderWindow& window);
		bool update(float deltaTime);
		void draw(sf::RenderWindow& window);

		void pushGameState(EGameStateType stateType, bool isExclusivelyVisible);

		void popGameState();

		void switchGameState(EGameStateType newState);
	};
}