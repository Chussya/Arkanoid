#pragma once

#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{
	class Game;

	enum class EGameStateType
	{
		None = 0,
		Playing,
		Complexity,
		GameOver,
		Leaderboard,
		MainMenu,
		Options,
		Pause,
		ExitDialog,
		Exit,
	};

	enum class EGameStateChangeType
	{
		None,
		Push,
		Pop,
		Switch
	};

	class GameState
	{
	private:
		EGameStateType type = EGameStateType::None;
		void* data = nullptr;
		bool isExclusivelyVisible = false;

	public:
		GameState(EGameStateType type, void* data, bool isExclusivelyVisible);

		bool isVisible();

		void InitGameState(Game& game);
		void ShutdownGameState(Game& game);
		void HandleWindowEventGameState(Game& game, sf::Event& event);
		void UpdateGameState(Game& game, float deltaTime);
		void DrawGameState(Game& game, sf::RenderWindow& window);
	};
}