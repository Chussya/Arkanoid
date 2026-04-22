#include "GameState.h"

#include <cassert>

#include "Game.h"
#include "GameStatePlaying.h"

namespace ArkanoidGame
{
	GameState::GameState() : type{ EGameStateType::None }, data{ nullptr }, isExclusivelyVisible{ false } {}
	GameState::GameState(GameState&& state) { operator=(std::move(state)); }
	GameState::GameState(EGameStateType type, bool isExclusivelyVisible) : type{type}, isExclusivelyVisible{ isExclusivelyVisible } {}

	GameState::~GameState()
	{
		switch (type)
		{
		case EGameStateType::MainMenu:
		{
			//ShutdownGameStateMainMenu(*(GameStateMainMenuData*)state.data, game);
			//delete (GameStateMainMenuData*)state.data;
			break;
		}
		case EGameStateType::Complexity:
		{
			//ShutdownGameStateComplexity(*(GameStateComplexityData*)state.data, game);
			//delete (GameStateComplexityData*)state.data;
			break;
		}
		case EGameStateType::Leaderboard:
		{
			//ShutdownGameStateLeaderboard(*(GameStateLeaderboardData*)state.data, game);
			//delete (GameStateLeaderboardData*)state.data;
			break;
		}
		case EGameStateType::Options:
		{
			//ShutdownGameStateOptions(*(GameStateOptionsData*)state.data, game);
			//delete (GameStateOptionsData*)state.data;
			break;
		}
		case EGameStateType::Playing:
		{
			delete ((GameStatePlayingData*)data);
			break;
		}
		case EGameStateType::Pause:
		{
			//ShutdownGameStatePause(*(GameStatePauseData*)state.data, game);
			//delete (GameStatePauseData*)state.data;
			break;
		}
		case EGameStateType::GameOver:
		{
			//ShutdownGameStateGameOver(*(GameStateGameOverData*)state.data, game);
			//delete (GameStateGameOverData*)state.data;
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game statee
			break;
		}

		data = nullptr;
	}

	bool GameState::isVisible()
	{
		return isExclusivelyVisible;
	}

	void GameState::init()
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
			//state.data = new GameStateOptionsData();
			//InitGameStateOptions(*(GameStateOptionsData*)state.data, game);
			break;
		}
		case EGameStateType::Playing:
		{
			data = new GameStatePlayingData();
			((GameStatePlayingData*)data)->init();
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
	}

	void GameState::handleWindowEvent(sf::Event& event)
	{
		switch (type)
		{
		case EGameStateType::MainMenu:
		{
			//HandleGameStateMainMenuWindowEvent(*(GameStateMainMenuData*)state.data, game, event);
			break;
		}
		case EGameStateType::Complexity:
		{
			//HandleGameStateComplexityWindowEvent(*(GameStateComplexityData*)state.data, game, event);
			break;
		}
		case EGameStateType::Leaderboard:
		{
			//HandleGameStateLeaderboardWindowEvent(*(GameStateLeaderboardData*)state.data, game, event);
			break;
		}
		case EGameStateType::Options:
		{
			//HandleGameStateOptionsWindowEvent(*(GameStateOptionsData*)state.data, game, event);
			break;
		}
		case EGameStateType::Playing:
		{
			((GameStatePlayingData*)data)->handleWindowEvent(event);
			break;
		}
		case EGameStateType::Pause:
		{
			//HandleGameStatePauseWindowEvent(*(GameStatePauseData*)state.data, game, event);
			break;
		}
		case EGameStateType::GameOver:
		{
			//HandleGameStateGameOverWindowEvent(*(GameStateGameOverData*)state.data, game, event);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game statee
			break;
		}
	}

	void GameState::update(float deltaTime)
	{
		switch (type)
		{
		case EGameStateType::MainMenu:
		{
			//UpdateGameStateMainMenu(*(GameStateMainMenuData*)state.data, game);
			break;
		}
		case EGameStateType::Complexity:
		{
			//UpdateGameStateComplexity(*(GameStateComplexityData*)state.data, game);
			break;
		}
		case EGameStateType::Leaderboard:
		{
			//UpdateGameStateLeaderboard(*(GameStateLeaderboardData*)state.data, game);
			break;
		}
		case EGameStateType::Options:
		{
			//UpdateGameStateOptions(*(GameStateOptionsData*)state.data, game);
			break;
		}
		case EGameStateType::Playing:
		{
			((GameStatePlayingData*)data)->update(deltaTime);
			break;
		}
		case EGameStateType::Pause:
		{
			//UpdateGameStatePause(*(GameStatePauseData*)state.data, game);
			break;
		}
		case EGameStateType::GameOver:
		{
			//UpdateGameStateGameOver(*(GameStateGameOverData*)state.data, game);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game statee
			break;
		}
	}

	void GameState::draw(sf::RenderWindow& window)
	{
		switch (type)
		{
		case EGameStateType::MainMenu:
		{
			//DrawGameStateMainMenu(*(GameStateMainMenuData*)state.data, game, window);
			break;
		}
		case EGameStateType::Complexity:
		{
			//DrawGameStateComplexity(*(GameStateComplexityData*)state.data, game, window);
			break;
		}
		case EGameStateType::Leaderboard:
		{
			//DrawGameStateLeaderboard(*(GameStateLeaderboardData*)state.data, game, window);
			break;
		}
		case EGameStateType::Options:
		{
			//DrawGameStateOptions(*(GameStateOptionsData*)state.data, game, window);
			break;
		}
		case EGameStateType::Playing:
		{
			((GameStatePlayingData*)data)->draw(window);
			break;
		}
		case EGameStateType::Pause:
		{
			//DrawGameStatePause(*(GameStatePauseData*)state.data, game, window);
			break;
		}
		case EGameStateType::GameOver:
		{
			//DrawGameStateGameOver(*(GameStateGameOverData*)state.data, game, window);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game statee
			break;
		}
	}
}