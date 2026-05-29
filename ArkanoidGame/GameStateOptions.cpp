#include "GameStateOptions.h"

#include <cassert>

#include "Util.h"
#include "Application.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
	void GameStateOptionsData::init()
	{
		// Init Fonts

		assert(font.loadFromFile(GAME_SETTINGS.FONT_PATH + "Roboto-Light.ttf"));

		// Init Texts

		Util::UGraphic::initText(title, "OPTIONS", font, sf::Color::Yellow, 60);
		Util::UGraphic::setItemOrigin(title, 0.5f, 0.5f);

		MenuItem<call> sound;

		sound.initMenuItem(
			"Sound",
			font,
			40,
			[]()
			{
				GAME_SETTINGS.getSoundVolume() > 0.f ? GAME_SETTINGS.setSoundLoud(0.f) : GAME_SETTINGS.setSoundLoud(20.f);
			}
		);
		sound.setItemOrigin(0.5f, 0.5f);
		sound.setPressed(GAME_SETTINGS.getSoundVolume() > 0.f);

		sf::RectangleShape soundCheckbox;
		soundCheckbox.setSize({ 40.f, 40.f });
		soundCheckbox.setOutlineColor(sf::Color::White);
		soundCheckbox.setOutlineThickness(2.f);
		soundCheckbox.setFillColor(GAME_SETTINGS.getSoundVolume() > 0.f ? sf::Color::Green : sf::Color::Black);

		MenuItem<call> music;

		music.initMenuItem(
			"Music",
			font,
			40,
			[]()
			{
				GAME_SETTINGS.getMusicVolume() > 0.f ? GAME_SETTINGS.setMusicLoud(0.f) : GAME_SETTINGS.setMusicLoud(20.f);
				Application::getInstance().getGame().getAudio().setMusicVolume(GAME_SETTINGS.getMusicVolume());
			}
		);
		music.setItemOrigin(0.5f, 0.5f);
		music.setPressed(GAME_SETTINGS.getMusicVolume() > 0.f);

		sf::RectangleShape musicCheckbox;
		musicCheckbox.setSize({ 40.f, 40.f });
		musicCheckbox.setOutlineColor(sf::Color::White);
		musicCheckbox.setOutlineThickness(2.f);
		musicCheckbox.setFillColor(GAME_SETTINGS.getMusicVolume() > 0.f ? sf::Color::Green : sf::Color::Black);

		buttons.push_back({ sound, soundCheckbox });
		buttons.push_back({ music, musicCheckbox });

		it = buttons.begin();
	}

	void GameStateOptionsData::handleWindowEvent(const sf::Event & event)
	{
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::B || event.key.code == sf::Keyboard::Escape)
			{
				Application::getInstance().getGame().exitGame();
			} else if (event.key.code == sf::Keyboard::Up)
			{
				if (it == buttons.begin())
				{
					it = buttons.end();
				}
				--it;
			} else if (event.key.code == sf::Keyboard::Down)
			{
				++it;

				if (it == buttons.end())
				{
					it = buttons.begin();
				}
			} else if (event.key.code == sf::Keyboard::Enter)
			{
				it->first.clickEvent();
			}
		}
	}

	void GameStateOptionsData::draw(sf::RenderWindow & window)
	{
		float yCoordinate = 30.f;

		title.setPosition(window.getSize().x / 2.f, yCoordinate);
		window.draw(title);

		yCoordinate += 100.f;

		for (auto& button : buttons)
		{
			button.second.setPosition(500.f, yCoordinate);
			window.draw(button.second);

			button.first.setItemPosition(300.f, yCoordinate);
			button.first.drawMenuItem(window);
			yCoordinate += 80.f;
		}
	}

	void GameStateOptionsData::update(float deltaTime)
	{
		for (auto button = buttons.begin(); button != buttons.end(); ++button)
		{
			if (button->first == it->first)
			{
				button->first.onFocus();
			} else
			{
				button->first.lostFocus();
			}

			button->first.isPressed()
				? button->second.setFillColor(sf::Color::Green)
				: button->second.setFillColor(sf::Color::Black);
		}
	}
}