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
		SwitchGameState(EGameStateType::Playing);
	}

	Game::~Game()
	{
		// Shutdown all game states
		while (this->gameStateStack.size() > 0)
		{
			gameStateStack.back().ShutdownGameState(*this);
			this->gameStateStack.pop_back();
		}

		this->gameStateChangeType = EGameStateChangeType::None;
		this->pendingGameStateType = EGameStateType::None;
		this->pendingGameStateIsExclusivelyVisible = false;
	}

	GameSettings Game::getGameSettigns()
	{
		return this->gameSettings;
	}

	void Game::HandleWindowEvents(sf::RenderWindow& window)
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
				gameStateStack.back().HandleWindowEventGameState(*this, event);
			}
		}
	}

	bool Game::UpdateGame(float deltaTime)
	{
		if (this->gameStateChangeType == EGameStateChangeType::Switch)
		{
			// Shutdown all game states
			while (this->gameStateStack.size() > 0)
			{
				gameStateStack.back().ShutdownGameState(*this);
				this->gameStateStack.pop_back();
			}
		} else if (this->gameStateChangeType == EGameStateChangeType::Pop)
		{
			// Shutdown only current game state
			if (this->gameStateStack.size() > 0)
			{
				gameStateStack.back().ShutdownGameState(*this);
				this->gameStateStack.pop_back();
			}
		}

		// Initialize new game state if needed
		if (this->pendingGameStateType != EGameStateType::None && this->pendingGameStateType != EGameStateType::Exit)
		{
			this->gameStateStack.push_back({ this->pendingGameStateType, nullptr, this->pendingGameStateIsExclusivelyVisible });
			gameStateStack.back().InitGameState(*this);
		}

		this->gameStateChangeType = EGameStateChangeType::None;
		this->pendingGameStateType = EGameStateType::None;
		this->pendingGameStateIsExclusivelyVisible = false;

		if (this->gameStateStack.size() > 0)
		{
			this->gameStateStack.back().UpdateGameState(*this, deltaTime);
			return true;
		}
		return false;
	}

	void Game::DrawGame(sf::RenderWindow& window)
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
				(*it)->DrawGameState(*this, window);
			}
		}
	}

	void Game::PushGameState(EGameStateType stateType, bool isExclusivelyVisible)
	{
		this->pendingGameStateType = stateType;
		this->pendingGameStateIsExclusivelyVisible = isExclusivelyVisible;
		this->gameStateChangeType = EGameStateChangeType::Push;
	}

	void Game::PopGameState()
	{
		this->pendingGameStateType = EGameStateType::None;
		this->pendingGameStateIsExclusivelyVisible = false;
		this->gameStateChangeType = EGameStateChangeType::Pop;
	}

	void Game::SwitchGameState(EGameStateType newState)
	{
		this->pendingGameStateType = newState;
		this->pendingGameStateIsExclusivelyVisible = false;
		this->gameStateChangeType = EGameStateChangeType::Switch;
	}
}
