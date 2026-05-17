#pragma once

#include <array>

namespace ArkanoidGame
{
	enum class BrickType
	{
		Unbreackable = 0,
		Simple,
		Durable
	};

	// 14 - rows of bricks
	// 5  - columns of bricks
	using BricksRow = std::array<BrickType, 14>;
	using BricksTemplate = std::array<BricksRow, 5>;

	class LevelManager
	{
	private:
		const int maxLevel{ 3 };

	public:
		int getMaxLevel() const;

		BricksTemplate loadLevel(int levelNum);
	};
}