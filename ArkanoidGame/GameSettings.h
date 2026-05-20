#pragma once

#include <string>

namespace ArkanoidGame
{
	class GameSettings
	{
	private:

		GameSettings() = default;

		// Music

		const float MAX_SOUND_VOLUME{ 20.f };
		const float MAX_MUSIC_VOLUME{ 20.f };

		float soundVolume{ MAX_SOUND_VOLUME };
		float musicVolume{ MAX_MUSIC_VOLUME };

		// Game physix

		float shellSpeed{ 400.f };
		float fadeSpeed{ 100.f };

	public:
		// Constants
		// Paths

		const std::string RESOURCES_PATH{ "Resources/" };
		const std::string IMG_PATH{ "Image/" };
		const std::string FONT_PATH{ RESOURCES_PATH + "Font/" };
		const std::string SOUND_PATH{ RESOURCES_PATH + "Audio/Sound/" };
		const std::string MUSIC_PATH{ RESOURCES_PATH + "Audio/Music/" };
		const std::string CONFIG_PATH{ RESOURCES_PATH + "Config/" };

		// Display

		const float TIME_PER_FRAME{ 1.f / 144.f };	// 144 fps
		const int SCREEN_WIDTH_GAME{ 800 };
		const int SCREEN_HEIGHT_GAME{ 600 };
		const int SCREEN_WIDTH_EDIT{ 300 };
		const int SCREEN_HEIGHT_EDIT{ 100 };
		const int SCREEN_WIDTH_POPUP{ 500 };
		const int SCREEN_HEIGHT_POPUP{ 300 };

		// Game

		const int TRIES_COUNT{ 3 };

		const int BRICKS_COUNT_ROW{ 14 };
		const int BRICKS_COUNT_COL{ 14 };
		const float BRICK_WIDTH_DEFAULT{ 40.f };
		const float BRICK_HEIGHT_DEFAULT{ 20.f };
		const float BRICK_SHIFT_WIDTH{ 10.f };
		const float BRICK_SHIFT_HEIGHT{ 25.f };

		const float BONUS_SPEED{ 200.f };
		const float EFFECT_DURATION{ 10.f };
		const float EFFECT_FALL_SPEED{ 100.f };
		const int CHANCE_EFFECT{ 10 };
		const float EFFECT_WIDTH{ 20.f };
		const float EFFECT_HEIGHT{ 20.f };

		const float PLATFORM_WIDTH_DEFAULT{ 90.f };
		const float PLATFORM_HEIGHT_DEFAULT{ 20.f };

		const float BALL_RADIUS_DEFAULT{ 10.f };

		const int MAX_LEVEL{ 3 };

		// Leaderboard

		const char SYM_SEPARATE{ '.' };
		const char SYM_TITLE{ '=' };
		const unsigned int ROW_LENGTH{ 50 };
		const std::string PLAYER_NAME_DEFAULT{ "XYZ" };
		const int PLAYER_NAME_LENGTH{ 25 };

		// Single instance of game settings
		static GameSettings& getInstance()
		{
			static GameSettings gameSettings;
			return gameSettings;
		}

		// Getters

		float getSoundVolume();
		float getMusicVolume();
		float getShellSpeed();
		float getFadeSpeed();

		// Setters

		void setSoundLoud(float soundLoud);
		void setMusicLoud(float musicLoud);
		void setShellSpeed(float shellSpeed);
	};
}

#define GAME_SETTINGS GameSettings::getInstance()