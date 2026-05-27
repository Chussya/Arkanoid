#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "GameStateData.h"

namespace ArkanoidGame
{
	class Game;

	enum class EGameStateType
	{
		None = 0,
		Playing,
		GameOver,
		Victory,
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
		EGameStateType type{ EGameStateType::None };
		std::shared_ptr<GameStateData> data{ nullptr };
		bool isExclusivelyVisible{ false };

	public:
		// Constructors and Destructor

		GameState() : type{ EGameStateType::None }, data{ nullptr }, isExclusivelyVisible{ false } {}
		GameState(EGameStateType type, bool isExclusivelyVisible);
		GameState(GameState&& state) noexcept { operator=(std::move(state)); }

		GameState(const GameState&) = delete;

		~GameState();

		// Operators

		GameState& operator=(const GameState&) = delete;

		GameState& operator=(GameState&& state) noexcept
		{
			type = state.type;
			data = std::move(state.data);
			isExclusivelyVisible = state.isExclusivelyVisible;
			state.data = nullptr;
			return *this;
		}

		// Getters

		EGameStateType getType() const;

		template<class T>
		T* getData() const
		{
			return static_cast<T*>(data.get());
		}

		// Methods

		bool isVisible();

		void handleWindowEvent(sf::Event& event);
		void update(float deltaTime);
		void draw(sf::RenderWindow& window);
	};
}