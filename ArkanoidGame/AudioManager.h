#pragma once

#include <unordered_map>
#include <SFML/Audio.hpp>

namespace ArkanoidGame
{
	class AudioManager
	{
	public:
		enum class ESoundEffect
		{
			Death = 1,
			Hit,
			Effect,
			Fail,
			Victory,
		};

	private:
		std::unordered_map<ESoundEffect, sf::SoundBuffer> sounds;
		sf::Music music;

	public:
		void loadMusic(const std::string path);
		void loadSoundBuffer(const ESoundEffect eSoundEffect, const std::string& path);

		sf::SoundBuffer& getSoundBuffer(const ESoundEffect eSoundEffect);

		bool isMusicPlaying();

		void setMusicVolume(const float volume);

		void playFullSound(const ESoundEffect eSoundEffect);
		void playMusic();
		void stopMusic();
	};
}