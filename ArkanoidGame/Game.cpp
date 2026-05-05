#include "Game.h"

#include <cassert>

namespace ArkanoidGame
{
	Game::Game()
	{
		gameStateChangeType = EGameStateChangeType::None;
		pendingGameStateType = EGameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;

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
