#include "GameStateMainMenu.h"

#include <cassert>

#include "Util.h"
#include "MenuItem.h"
#include "Application.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
	void GameStateMainMenuData::handleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Up)
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
				it->clickEvent();
			}
		}
	}

	void GameStateMainMenuData::init()
	{
		// Init music
		if (!Application::getInstance().getGame().getAudio().isMusicPlaying())
		{
			Application::getInstance().getGame().getAudio().loadMusic(GAME_SETTINGS.MUSIC_PATH + "Menu.ogg");
			Application::getInstance().getGame().getAudio().setMusicVolume(GAME_SETTINGS.getMusicVolume());
			Application::getInstance().getGame().getAudio().playMusic();
		}

		// Init Fonts

		assert(font.loadFromFile(GAME_SETTINGS.FONT_PATH + "Roboto-Light.ttf"));

		// Init Texts

		Util::UGraphic::initText(title, "ARKANOID GAME", font, sf::Color::Yellow, 60);
		Util::UGraphic::setItemOrigin(title, 0.5f, 0.5f);

		// Init buttons

		MenuItem<call> startGame;

		startGame.initMenuItem(
			"Start game",
			font,
			40,
			[]()
			{
				Application::getInstance().getGame().getAudio().stopMusic();
				Application::getInstance().getGame().startGame();
			}
		);
		startGame.setItemOrigin(0.5f, 0.5f);

		MenuItem<call> leaderboard;

		leaderboard.initMenuItem(
			"Leaderboard",
			font,
			40,
			[]() { Application::getInstance().getGame().showLeaderboards(); }
		);
		leaderboard.setItemOrigin(0.5f, 0.5f);

		MenuItem<call> options;

		options.initMenuItem(
			"Options",
			font,
			40,
			[]() { Application::getInstance().getGame().showOptions(); }
		);
		options.setItemOrigin(0.5f, 0.5f);

		MenuItem<call> exit;

		exit.initMenuItem(
			"Exit",
			font,
			40,
			[]()
			{
				Application::getInstance().getGame().getAudio().stopMusic();
				Application::getInstance().getGame().quitGame();
			}
		);
		exit.setItemOrigin(0.5f, 0.5f);

		buttons.push_back(startGame);
		buttons.push_back(leaderboard);
		buttons.push_back(options);
		buttons.push_back(exit);

		it = buttons.begin();
	}

	void GameStateMainMenuData::draw(sf::RenderWindow& window)
	{
		float yCoordinate = 30.f;

		// Draw title
		title.setPosition(window.getSize().x / 2.f, yCoordinate);
		window.draw(title);

		// Draw buttons
		yCoordinate += 100.f;

		for (auto& button : buttons)
		{
			button.setItemPosition(window.getSize().x / 2.f, yCoordinate);
			button.drawMenuItem(window);
			yCoordinate += 80.f;
		}
	}

	void GameStateMainMenuData::update(float deltaTime)
	{
		for (auto button = buttons.begin(); button != buttons.end(); ++button)
		{
			if (*button == *it)
			{
				button->onFocus();
			} else
			{
				button->lostFocus();
			}
		}
	}
}