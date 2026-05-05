#pragma once

#include <string>

namespace ArkanoidGame
{
	class GameSettings
	{
	private:

		GameSettings() = default;

		// Music

		float soundLoud{ 20.f };
		float musicLoud{ 20.f };

		// Game physix

		float shellSpeed{ 400.f };
		float fadeSpeed{ 100.f };

		// Other

		std::string playerName{ PLAYER_NAME_DEFAULT };

	public:
		// Constants
		// Path

		const std::string RESOURCES_PATH{ "Resources/" };
		const std::string IMG_PATH{ "Images/" };

		// Display

		const float TIME_PER_FRAME{ 1.f / 144.f };	// 144 fps
		const int SCREEN_WIDTH_GAME{ 800 };
		const int SCREEN_HEIGHT_GAME{ 600 };
		const int SCREEN_WIDTH_EDIT{ 300 };
		const int SCREEN_HEIGHT_EDIT{ 100 };

		// Game

		const int BRICKS_COUNT{ 10 };
		const float BONUS_SPEED{ 100.f };
		const float PLATFORM_WIDTH_DEFAULT{ 90.f };
		const float PLATFORM_HEIGHT_DEFAULT{ 20.f };
		const float BRICK_WIDTH_DEFAULT{ 80.f };
		const float BRICK_HEIGHT_DEFAULT{ 20.f };
		const float BALL_RADIUS_DEFAULT{ 10.f };

		// Leaderboard

		const char SYM_SEPARATE{ '.' };
		const char SYM_TITLE{ '=' };
		const unsigned int ROW_LENGTH{ 50 };
		const std::string PLAYER_NAME_DEFAULT{ "XYZ" };
		const int PLAYER_NAME_LENGTH{ 25 };

		// Single instance of game settings
		static GameSettings& Instance()
		{
			static GameSettings gameSettings;
			return gameSettings;
		}

		// Getters

		float getSoundLoud();
		float getMusicLoud();
		float getShellSpeed();
		float getFadeSpeed();
		std::string getPlayerName();

		// Setters

		void setSoundLoud(float soundLoud);
		void setMusicLoud(float musicLoud);
		void setShellSpeed(float shellSpeed);
		void setPlayerName(std::string playerName);
	};
}

#define GAME_SETTINGS GameSettings::Instance()