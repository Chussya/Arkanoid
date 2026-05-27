#include "Game.h"

#include <cassert>

#include "GameStatePlaying.h"

namespace ArkanoidGame
{
	// Private

	void Game::handleWindowEvents(sf::RenderWindow& window)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window if close button or Escape key pressed
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (stateStack.size() > 0)
			{
				stateStack.back().handleWindowEvent(event);
			}
		}
	}

	bool Game::update(float deltaTime)
	{
		if (gameStateChangeType == EGameStateChangeType::Switch)
		{
			// Shutdown all game states
			while (stateStack.size() > 0)
			{
				stateStack.pop_back();
			}
		} else if (gameStateChangeType == EGameStateChangeType::Pop)
		{
			// Shutdown only current game state
			if (stateStack.size() > 0)
			{
				stateStack.pop_back();
			}
		}

		// Initialize new game state if needed
		if (pendingGameStateType != EGameStateType::None && pendingGameStateType != EGameStateType::Exit)
		{
			stateStack.push_back(GameState{ pendingGameStateType, pendingGameStateIsExclusivelyVisible });
		}

		gameStateChangeType = EGameStateChangeType::None;
		pendingGameStateType = EGameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;

		if (stateStack.size() > 0)
		{
			stateStack.back().update(deltaTime);
			return true;
		}
		return false;
	}

	void Game::draw(sf::RenderWindow& window)
	{
		if (stateStack.size() > 0)
		{
			std::vector<GameState*> visibleGameStates;
			for (auto it = stateStack.rbegin(); it != stateStack.rend(); ++it)
			{
				visibleGameStates.push_back(&(*it));
				if (it->isVisible())
				{
					break;
				}
			}
			for (auto it = visibleGameStates.rbegin(); it != visibleGameStates.rend(); ++it)
			{
				(*it)->draw(window);
			}
		}
	}

	void Game::pushGameState(EGameStateType stateType, bool isExclusivelyVisible)
	{
		pendingGameStateType = stateType;
		pendingGameStateIsExclusivelyVisible = isExclusivelyVisible;
		gameStateChangeType = EGameStateChangeType::Push;
	}

	void Game::switchGameState(EGameStateType newState)
	{
		pendingGameStateType = newState;
		pendingGameStateIsExclusivelyVisible = false;
		gameStateChangeType = EGameStateChangeType::Switch;
	}

	// Public

	Game::Game()
	{
		// Generate fake records table
		playerRecord = { GAME_SETTINGS.PLAYER_NAME_DEFAULT, 0 };
		records = { {playerRecord.first, playerRecord.second} };

		gameStateChangeType = EGameStateChangeType::None;
		pendingGameStateType = EGameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;

		audio.loadSoundBuffer(AudioManager::ESoundEffect::Hit, GAME_SETTINGS.SOUND_PATH + "hit.wav");
		audio.loadSoundBuffer(AudioManager::ESoundEffect::Fail, GAME_SETTINGS.SOUND_PATH + "fail.wav");
		audio.loadSoundBuffer(AudioManager::ESoundEffect::Death, GAME_SETTINGS.SOUND_PATH + "death.wav");
		audio.loadSoundBuffer(AudioManager::ESoundEffect::Effect, GAME_SETTINGS.SOUND_PATH + "effect.wav");
		audio.loadSoundBuffer(AudioManager::ESoundEffect::Victory, GAME_SETTINGS.SOUND_PATH + "victory.wav");

		switchGameState(EGameStateType::MainMenu);
	}

	Game::~Game()
	{
		// Shutdown all game states
		while (stateStack.size() > 0)
		{
			stateStack.pop_back();
		}

		gameStateChangeType = EGameStateChangeType::None;
		pendingGameStateType = EGameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;

		records.clear();
	}

	void Game::setPlayerRecord(Record record)
	{
		playerRecord = record;
	}

	Record Game::getPlayerRecord()
	{
		return playerRecord;
	}

	RecordsMap Game::getRecords()
	{
		return records;
	}

	AudioManager& Game::getAudio()
	{
		return audio;
	}

	RecordsVector Game::getSortedRecords()
	{
		RecordsVector vRecords(records.begin(), records.end());

		std::sort(vRecords.begin(), vRecords.end(), [](std::pair<std::string, int> record1, std::pair<std::string, int> record2) { return record1.second > record2.second; });

		return vRecords;
	}

	void Game::updateRecords(Record record)
	{
		if (records.size() == 1 && records.begin()->second == 0)
		{
			records.clear();
			records.insert({ record.first, record.second });
		} else
		{
			auto foundIt = records.find(record.first);

			if (foundIt != records.end())
			{
				records[record.first] = record.second;
			} else
			{
				records.insert({ record.first, record.second });
			}
		}
	}

	void Game::restartPlayerScore()
	{
		playerRecord.second = 0;
	}

	void Game::popGameState()
	{
		pendingGameStateType = EGameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
		gameStateChangeType = EGameStateChangeType::Pop;
	}

	void Game::startGame()
	{
		switchGameState(EGameStateType::Playing);
	}

	void Game::pauseGame()
	{
		pushGameState(EGameStateType::Pause, false);
	}

	void Game::winGame()
	{
		pushGameState(EGameStateType::Victory, false);
	}

	void Game::looseGame()
	{
		switchGameState(EGameStateType::GameOver);
	}

	void Game::quitGame()
	{
		switchGameState(EGameStateType::Exit);
	}

	void Game::exitGame()
	{
		switchGameState(EGameStateType::MainMenu);
	}

	void Game::showOptions()
	{
		switchGameState(EGameStateType::Options);
	}

	void Game::showLeaderboards()
	{
		pushGameState(EGameStateType::Leaderboard, true);
	}

	void Game::loadNextLevel()
	{
		assert(stateStack.back().getType() == EGameStateType::Playing);
		auto playingData = (stateStack.back().getData<GameStatePlayingData>());
		playingData->loadNextLevel();
	}

	void Game::updateGame(float timeDelta, sf::RenderWindow& window)
	{
		handleWindowEvents(window);

		if (update(timeDelta))
		{
			// Draw everything here
			// Clear the window first
			window.clear();

			draw(window);

			// End the current frame, display window contents on screen
			window.display();
		} else
		{
			window.close();
		}
	}
}
