#include "LevelManager.h"

#include <iostream>
#include <fstream>
#include <cassert>

#include "Util.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
	int LevelManager::getMaxLevel() const
	{
		return maxLevel;
	}

	BricksTemplate LevelManager::loadLevel(int levelNum)
	{
		const std::string fileName{ "levels.config" };

		std::fstream file{ GAME_SETTINGS.CONFIG_PATH + fileName };

		BricksTemplate arr;

		if (file.is_open())
		{
			bool isFound{ false };

			int row{ 0 };
			int col{ 0 };

			const std::string lvl{ "#" + std::to_string(levelNum) };
			std::string line;

			while (std::getline(file, line))
			{
				if (line.find(lvl) != std::string::npos)
				{
					isFound = true;
				} else if (isFound)
				{
					if (Util::UString::isNumeric(line))
					{
						std::for_each(line.begin(), line.end(),
							[&](const char c)
							{
								arr[row][col] = static_cast<BrickType>(c - '0');
								++col;
							});
						col = 0;
						++row;
					} else
					{
						break;
					}
				}
			}

		} else
		{
			assert(false);
		}
		return arr;
	}
}
