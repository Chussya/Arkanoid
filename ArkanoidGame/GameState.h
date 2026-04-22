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
		// Constructors and Destructor

		GameState();
		GameState(EGameStateType type, bool isExclusivelyVisible);
		GameState(GameState&& state);

		GameState(const GameState&) = delete; // don't need copy constructor because of this class has pointer data (void*)

		~GameState();

		// Operators

		GameState& operator=(const GameState&) = delete;

		GameState& operator= (GameState&& state) noexcept
		{
			type = state.type;
			data = std::move(state.data);
			isExclusivelyVisible = state.isExclusivelyVisible;
			state.data = nullptr;
			return *this;
		}

		// Methods

		bool isVisible();

		void init();
		void handleWindowEvent(sf::Event& event);
		void update(float deltaTime);
		void draw(sf::RenderWindow& window);
	};
}