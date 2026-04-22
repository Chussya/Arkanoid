#include "Game.h"

#include <cassert>

//#include "Record.h"
//#include "GameStateMainMenu.h"
//#include "GameStateLeaderboard.h"
//#include "GameStateOptions.h"
//#include "GameStateComplexity.h"
//#include "GameStatePause.h"
//#include "GameStateGameOver.h"

namespace ArkanoidGame
{
	Game::Game()
	{
		this->gameStateChangeType = EGameStateChangeType::None;
		this->pendingGameStateType = EGameStateType::None;
		this->pendingGameStateIsExclusivelyVisible = false;
		//SwitchGameState(EGameStateType::MainMenu);
		switchGameState(EGameStateType::Playing);
	}

	Game::~Game()
	{
		// Shutdown all game states
		while (this->gameStateStack.size() > 0)
		{
			this->gameStateStack.pop_back();
		}

		this->gameStateChangeType = EGameStateChangeType::None;
		this->pendingGameStateType = EGameStateType::None;
		this->pendingGameStateIsExclusivelyVisible = false;
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

			if (this->gameStateStack.size() > 0)
			{
				gameStateStack.back().handleWindowEvent(event);
			}
		}
	}

	bool Game::update(float deltaTime)
	{
		if (this->gameStateChangeType == EGameStateChangeType::Switch)
		{
			// Shutdown all game states
			while (this->gameStateStack.size() > 0)
			{
				this->gameStateStack.pop_back();
			}
		} else if (this->gameStateChangeType == EGameStateChangeType::Pop)
		{
			// Shutdown only current game state
			if (this->gameStateStack.size() > 0)
			{
				this->gameStateStack.pop_back();
			}
		}

		// Initialize new game state if needed
		if (this->pendingGameStateType != EGameStateType::None && this->pendingGameStateType != EGameStateType::Exit)
		{
			this->gameStateStack.push_back({ this->pendingGameStateType, this->pendingGameStateIsExclusivelyVisible });
			gameStateStack.back().init();
		}

		this->gameStateChangeType = EGameStateChangeType::None;
		this->pendingGameStateType = EGameStateType::None;
		this->pendingGameStateIsExclusivelyVisible = false;

		if (this->gameStateStack.size() > 0)
		{
			this->gameStateStack.back().update(deltaTime);
			return true;
		}
		return false;
	}

	void Game::draw(sf::RenderWindow& window)
	{
		if (this->gameStateStack.size() > 0)
		{
			std::vector<GameState*> visibleGameStates;
			for (auto it = this->gameStateStack.rbegin(); it != this->gameStateStack.rend(); ++it)
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
		this->pendingGameStateType = stateType;
		this->pendingGameStateIsExclusivelyVisible = isExclusivelyVisible;
		this->gameStateChangeType = EGameStateChangeType::Push;
	}

	void Game::popGameState()
	{
		this->pendingGameStateType = EGameStateType::None;
		this->pendingGameStateIsExclusivelyVisible = false;
		this->gameStateChangeType = EGameStateChangeType::Pop;
	}

	void Game::switchGameState(EGameStateType newState)
	{
		this->pendingGameStateType = newState;
		this->pendingGameStateIsExclusivelyVisible = false;
		this->gameStateChangeType = EGameStateChangeType::Switch;
	}
}
