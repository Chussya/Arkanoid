#include "GameState.h"

#include <cassert>

#include "Game.h"
#include "GameStatePlaying.h"

namespace ArkanoidGame
{
	GameState::GameState(EGameStateType type, bool isExclusivelyVisible) : type{type}, isExclusivelyVisible{ isExclusivelyVisible }
	{
		switch (type)
		{
		case EGameStateType::MainMenu:
		{
			//state.data = new GameStateMainMenuData();
			//InitGameStateMainMenu(*(GameStateMainMenuData*)state.data, game);
			break;
		}
		case EGameStateType::Complexity:
		{
			//state.data = new GameStateComplexityData();
			//InitGameStateComplexity(*(GameStateComplexityData*)state.data, game);
			break;
		}
		case EGameStateType::Leaderboard:
		{
			//state.data = new GameStateLeaderboardData();
			//InitGameStateLeaderboard(*(GameStateLeaderboardData*)state.data, game);
			break;
		}
		case EGameStateType::Options:
		{
			//data = std::make_unique<GameStateOptionsData>();
			break;
		}
		case EGameStateType::Playing:
		{
			data = std::make_unique<GameStatePlayingData>();
			break;
		}
		case EGameStateType::Pause:
		{
			//state.data = new GameStatePauseData();
			//InitGameStatePause(*(GameStatePauseData*)state.data, game);
			break;
		}
		case EGameStateType::GameOver:
		{
			//state.data = new GameStateGameOverData();
			//InitGameStateGameOver(*(GameStateGameOverData*)state.data, game);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game statee
			break;
		}
		if (data)
		{
			data->init();
		}
	}

	GameState::~GameState()
	{
		data = nullptr;
	}

	bool GameState::isVisible()
	{
		return isExclusivelyVisible;
	}

	void GameState::handleWindowEvent(sf::Event& event)
	{
		data->handleWindowEvent(event);
	}

	void GameState::update(float deltaTime)
	{
		data->update(deltaTime);
	}

	void GameState::draw(sf::RenderWindow& window)
	{
		data->draw(window);
	}
}