#include "Game.h"

#include <cassert>

namespace ArkanoidGame
{
	Game::Game()
	{
		// Generate fake records table
		playerRecord = { GAME_SETTINGS.PLAYER_NAME_DEFAULT, 0 };
		records = { {playerRecord.first, playerRecord.second} };

		gameStateChangeType = EGameStateChangeType::None;
		pendingGameStateType = EGameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;

		audio.loadSoundBuffer(AudioManager::ESoundEffect::Hit, GAME_SETTINGS.SOUND_PATH + "hit.wav");
		audio.loadSoundBuffer(AudioManager::ESoundEffect::Death, GAME_SETTINGS.SOUND_PATH + "death.wav");
		audio.loadSoundBuffer(AudioManager::ESoundEffect::Victory, GAME_SETTINGS.SOUND_PATH + "victory.wav");

		switchGameState(EGameStateType::MainMenu);
	}

	Game::~Game()
	{
		// Shutdown all game states
		while (gameStateStack.size() > 0)
		{
			gameStateStack.pop_back();
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
		if (records.size() == 0 && records.begin()->second == 0)
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

			if (gameStateStack.size() > 0)
			{
				gameStateStack.back().handleWindowEvent(event);
			}
		}
	}

	bool Game::update(float deltaTime)
	{
		if (gameStateChangeType == EGameStateChangeType::Switch)
		{
			// Shutdown all game states
			while (gameStateStack.size() > 0)
			{
				gameStateStack.pop_back();
			}
		} else if (gameStateChangeType == EGameStateChangeType::Pop)
		{
			// Shutdown only current game state
			if (gameStateStack.size() > 0)
			{
				gameStateStack.pop_back();
			}
		}

		// Initialize new game state if needed
		if (pendingGameStateType != EGameStateType::None && pendingGameStateType != EGameStateType::Exit)
		{
			gameStateStack.push_back(GameState{ pendingGameStateType, pendingGameStateIsExclusivelyVisible });
		}

		gameStateChangeType = EGameStateChangeType::None;
		pendingGameStateType = EGameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;

		if (gameStateStack.size() > 0)
		{
			gameStateStack.back().update(deltaTime);
			return true;
		}
		return false;
	}

	void Game::draw(sf::RenderWindow& window)
	{
		if (gameStateStack.size() > 0)
		{
			std::vector<GameState*> visibleGameStates;
			for (auto it = gameStateStack.rbegin(); it != gameStateStack.rend(); ++it)
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

	void Game::popGameState()
	{
		pendingGameStateType = EGameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
		gameStateChangeType = EGameStateChangeType::Pop;
	}

	void Game::switchGameState(EGameStateType newState)
	{
		pendingGameStateType = newState;
		pendingGameStateIsExclusivelyVisible = false;
		gameStateChangeType = EGameStateChangeType::Switch;
	}
}
