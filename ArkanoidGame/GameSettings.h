#pragma once

namespace ArkanoidGame
{
	// Path

	const std::string RESOURCES_PATH{ "Resources/" };

	// Display

	const float TIME_PER_FRAME{ 1.f / 144.f };	// 144 fps
	const int SCREEN_WIDTH_GAME{ 800 };
	const int SCREEN_HEIGHT_GAME{ 600 };

	// Game

	const float BONUS_SPEED{ 100.f };
	const float PLATFORM_WIDTH_DEFAULT{ 90.f };
	const float PLATFORM_HEIGHT_DEFAULT{ 20.f };
	const float BALL_RADIUS_DEFAULT{ 10.f };

	// Leaderboard

	const char SYM_SEPARATE{ '.' };
	const char SYM_TITLE{ '=' };
	const unsigned int ROW_LENGTH{ 50 };
	const std::string DEFAULT_PLAYER_NAME{ "XYZ" };
	const int PLAYER_NAME_LENGTH{ 25 };

	struct GameSettings
	{
		std::string playerName{ DEFAULT_PLAYER_NAME };

		float soundLoud{ 20.f };
		float musicLoud{ 20.f };

		float shellSpeed{ 400.f };
	};
}
