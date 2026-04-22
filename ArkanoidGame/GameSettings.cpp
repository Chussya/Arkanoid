#include "GameSettings.h"

namespace ArkanoidGame
{
	float GameSettings::getSoundLoud()
	{
		return soundLoud;
	}

	float GameSettings::getMusicLoud()
	{
		return musicLoud;
	}

	float GameSettings::getShellSpeed()
	{
		return shellSpeed;
	}

	std::string GameSettings::getPlayerName()
	{
		return playerName;
	}

	void GameSettings::setSoundLoud(float soundLoud)
	{
		this->soundLoud = soundLoud;
	}

	void GameSettings::setMusicLoud(float musicLoud)
	{
		this->musicLoud = musicLoud;
	}

	void GameSettings::setShellSpeed(float shellSpeed)
	{
		this->shellSpeed = shellSpeed;
	}

	void GameSettings::setPlayerName(std::string playerName)
	{
		this->playerName = playerName;
	}
}