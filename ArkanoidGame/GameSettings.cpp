#include "GameSettings.h"

namespace ArkanoidGame
{
	float GameSettings::getSoundVolume()
	{
		return soundVolume;
	}

	float GameSettings::getMusicVolume()
	{
		return musicVolume;
	}

	float GameSettings::getShellSpeed()
	{
		return shellSpeed;
	}

	float GameSettings::getFadeSpeed()
	{
		return fadeSpeed;
	}

	void GameSettings::setSoundLoud(float soundLoud)
	{
		this->soundVolume = soundLoud;
	}

	void GameSettings::setMusicLoud(float musicLoud)
	{
		this->musicVolume = musicLoud;
	}

	void GameSettings::setShellSpeed(float shellSpeed)
	{
		this->shellSpeed = shellSpeed;
	}
}