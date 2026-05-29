#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Record.h"
#include "GameState.h"
#include "GameSettings.h"
#include "AudioManager.h"
#include "LevelManager.h"

namespace ArkanoidGame
{
	class Game
	{
	private:
		std::vector<GameState> stateStack;
		EGameStateChangeType gameStateChangeType = EGameStateChangeType::None;
		EGameStateType pendingGameStateType = EGameStateType::None;
		bool pendingGameStateIsExclusivelyVisible = false;

		Record playerRecord;
		RecordsMap records;

		AudioManager audio;

		// General methods

		void handleWindowEvents(sf::RenderWindow& window);
		bool update(float deltaTime);
		void draw(sf::RenderWindow& window);

		// State methods

		void pushGameState(EGameStateType stateType, bool isExclusivelyVisible);
		void switchGameState(EGameStateType newState);

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

		// State methods

		void popGameState();

		// Game methods

		void startGame();
		void pauseGame();
		void winGame();
		void looseGame();
		void exitGame();
		void quitGame();
		void showOptions();
		void showLeaderboards();
		void loadNextLevel();
		void updateGame(float timeDelta, sf::RenderWindow& window);
	};
}