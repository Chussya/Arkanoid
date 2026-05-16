#pragma once

#include <array>

namespace ArkanoidGame
{
	// 14 - rows of bricks
	// 5  - columns of bricks
	using BricksRow = std::array<int, 14>;
	using BricksTemplate = std::array<BricksRow, 5>;

	class LevelManager
	{
	private:
		int levelNum{ 1 };
		BricksTemplate lvlVector;

		void loadLevel();
	public:
		LevelManager();

		// Getters

		BricksTemplate getLevel() const;

		// General methods

		void nextLevel();
	};
}