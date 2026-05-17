#include "GameState.h"

#include <cassert>

#include "Game.h"
#include "GameStatePlaying.h"
#include "GameStateMainMenu.h"
#include "GameStatePause.h"
#include "GameStateLeaderboard.h"
#include "GameStateOptions.h"
#include "GameStateVictory.h"
#include "GameStateGameOver.h"

namespace ArkanoidGame
{
	GameState::GameState(EGameStateType type, bool isExclusivelyVisible) : type{type}, isExclusivelyVisible{ isExclusivelyVisible }
	{
		switch (type)
		{
		case EGameStateType::MainMenu:
		{
			data = std::make_unique<GameStateMainMenuData>();
			break;
		}
		case EGameStateType::Leaderboard:
		{
			data = std::make_unique<GameStateLeaderboardData>();
			break;
		}
		case EGameStateType::Options:
		{
			data = std::make_unique<GameStateOptionsData>();
			break;
		}
		case EGameStateType::Playing:
		{
			data = std::make_unique<GameStatePlayingData>();
			break;
		}
		case EGameStateType::Pause:
		{
			data = std::make_unique<GameStatePauseData>();
			break;
		}
		case EGameStateType::Victory:
		{
			data = std::make_unique<GameStateVictoryData>();
			break;
		}
		case EGameStateType::GameOver:
		{
			data = std::make_unique<GameStateGameOverData>();
			break;
		}
		default:
			assert(false);
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

	EGameStateType GameState::getType() const
	{
		return type;
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