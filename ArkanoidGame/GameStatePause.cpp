#include "GameStatePause.h"

#include <cassert>

#include "Util.h"
#include "Application.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
	void GameStatePauseData::handleWindowEvent(const sf::Event& event)
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
			} else if (!isWaiting && event.key.code == sf::Keyboard::Enter)
			{
				if (it->getButtonName() == "Continue")
				{
					delayClock.restart();
					isWaiting = true;

				} else
				{
					it->clickEvent();
				}
			}
		}
	}

	void GameStatePauseData::init()
	{
		// Init Fonts

		assert(font.loadFromFile(GAME_SETTINGS.FONT_PATH + "Roboto-Light.ttf"));

		// Init Texts

		Util::UGraphic::initText(title, "PAUSE", font, sf::Color::Yellow, 40);
		Util::UGraphic::setItemOrigin(title, 0.5f, 0.5f);

		Util::UGraphic::initText(timer, timerText, font, sf::Color::Yellow, 50);
		Util::UGraphic::setItemOrigin(timer, 0.5f, 0.5f);

		// Init buttons

		MenuItem<call> exitMenu;
		exitMenu.initMenuItem(
			"Menu",
			font,
			30,
			[]() { Application::getInstance().getGame().exitGame(); }
		);
		exitMenu.setItemOrigin(0.5f, 0.5f);

		MenuItem<call> continueGame;

		continueGame.initMenuItem(
			"Continue",
			font,
			30,
			[]() { Application::getInstance().getGame().popGameState(); }
		);
		continueGame.setItemOrigin(0.5f, 0.5f);

		buttons.push_back(exitMenu);
		buttons.push_back(continueGame);

		it = buttons.begin();
	}

	void GameStatePauseData::draw(sf::RenderWindow& window)
	{
		// Draw title
		title.setPosition(window.getSize().x / 2.f, 200.f);
		window.draw(title);

		// Draw buttons
		if (!isWaiting)
		{
			float yCoordinate = 400.f;

			for (auto& button : buttons)
			{
				button.setItemPosition(window.getSize().x / 2.f, yCoordinate);
				button.drawMenuItem(window);
				yCoordinate += 80.f;
			}
		} else
		{
			timer.setPosition(GAME_SETTINGS.SCREEN_WIDTH_GAME / 2.f, 400.f);
			window.draw(timer);
		}
	}

	void GameStatePauseData::update(float deltaTime)
	{
		if (!isWaiting)
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
		} else
		{
			timer.setString(timerText + std::to_string(static_cast<int>(delayTime + 1 - delayClock.getElapsedTime().asSeconds())));

			if (delayClock.getElapsedTime().asSeconds() >= delayTime)
			{
				it->clickEvent();
			}
		}
	}
}