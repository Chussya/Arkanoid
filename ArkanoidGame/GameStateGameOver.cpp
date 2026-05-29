#include "GameStateGameOver.h"

#include <cassert>

#include "Util.h"
#include "Application.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
	void GameStateGameOverData::init()
	{
		// Init fonts
		assert(font.loadFromFile(GAME_SETTINGS.FONT_PATH + "arial.ttf"));
		assert(recordsFont.loadFromFile(GAME_SETTINGS.FONT_PATH + "consola.ttf"));

		// Save new records?
		popUpNewRecords();

		// Sort records
		RecordsVector records = Application::getInstance().getGame().getSortedRecords();

		if (records.size() > maxRecords)
		{
			records.resize(maxRecords);
		}

		// Leaderboard definition
		std::string tableOfLeaders;

		tableOfLeaders = Util::UString::stringCenter("LEADERBOARD", GAME_SETTINGS.SYM_TITLE, GAME_SETTINGS.ROW_LENGTH);
		tableOfLeaders.push_back('\n');

		for (auto record : records)
		{
			tableOfLeaders.append(Util::UString::stringFormat(record.first, std::to_string(record.second), GAME_SETTINGS.SYM_SEPARATE, GAME_SETTINGS.ROW_LENGTH)).push_back('\n');
		}

		std::string end = "";
		end.resize(GAME_SETTINGS.ROW_LENGTH, '=');
		tableOfLeaders.append(end);

		// Init texts
		Util::UGraphic::initText(gameOverText, "GAME OVER", font, sf::Color::Red, 40);
		Util::UGraphic::setItemOrigin(gameOverText, 0.5f, 0.5f);

		Util::UGraphic::initText(leaderBoardText, tableOfLeaders, recordsFont, sf::Color::White, 25);
		Util::UGraphic::setItemOrigin(leaderBoardText, 0.5f, 0.5f);

		// Init menu items

		MenuItem<call> continueGame;

		continueGame.initMenuItem(
			"Continue",
			font,
			30,
			[]() { Application::getInstance().getGame().startGame(); }
		);
		continueGame.setItemOrigin(0.5f, 0.5f);

		MenuItem<call> exitMenu;

		exitMenu.initMenuItem(
			"Menu",
			font,
			30,
			[]() { Application::getInstance().getGame().exitGame(); }
		);
		exitMenu.setItemOrigin(0.5f, 0.5f);

		buttons.push_back(continueGame);
		buttons.push_back(exitMenu);

		it = buttons.begin();
	}

	void GameStateGameOverData::handleWindowEvent(const sf::Event & event)
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
				Application::getInstance().getGame().restartPlayerScore();
				it->clickEvent();
			}
		}
	}

	void GameStateGameOverData::draw(sf::RenderWindow & window)
	{
		float yCoordinate = 30.f;

		// Set position
		gameOverText.setPosition(GAME_SETTINGS.SCREEN_WIDTH_GAME / 2.f, yCoordinate);
		leaderBoardText.setPosition(GAME_SETTINGS.SCREEN_WIDTH_GAME / 2.f, GAME_SETTINGS.SCREEN_HEIGHT_GAME / 2.f);

		yCoordinate = 500.f;

		for (auto& button : buttons)
		{
			button.setItemPosition(window.getSize().x / 2.f, yCoordinate);
			button.drawMenuItem(window);
			yCoordinate += 60.f;
		}

		// Draw game over window
		window.draw(gameOverText);
		window.draw(leaderBoardText);
	}

	void GameStateGameOverData::update(float deltaTime)
	{
		for (auto button = buttons.begin(); button != buttons.end(); ++button)
		{
			if (button == it)
			{
				button->onFocus();
			} else
			{
				button->lostFocus();
			}
		}
	}

	void GameStateGameOverData::popUpNewRecords()
	{
		sf::RenderWindow window(sf::VideoMode(GAME_SETTINGS.SCREEN_WIDTH_POPUP, GAME_SETTINGS.SCREEN_HEIGHT_POPUP), "Save record window");

		// Init texts and menu items

		sf::Text title;

		Util::UGraphic::initText(title, "Save new record as new?", font, sf::Color::White, 40);
		Util::UGraphic::setItemOrigin(title, 0.5f, 0.5f);
		title.setPosition(GAME_SETTINGS.SCREEN_WIDTH_POPUP / 2.f, 100);

		MenuItem<call> no;

		no.initMenuItem(
			"No",
			font,
			30
		);
		no.setItemOrigin(0.5f, 0.5f);

		no.setItemPosition(window.getSize().x / 2.f, 200);
		no.onFocus();

		MenuItem<call> yes;

		yes.initMenuItem(
			"Yes",
			font,
			30
		);
		yes.setItemOrigin(0.5f, 0.5f);
		yes.setItemPosition(window.getSize().x / 2.f, 250);

		window.display();

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

				if (event.type == sf::Event::KeyReleased)
				{
					if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down)
					{
						if (yes.isFocused())
						{
							yes.lostFocus();
							no.onFocus();
						} else
						{
							no.lostFocus();
							yes.onFocus();
						}
					} else if (event.key.code == sf::Keyboard::Enter)
					{
						if (yes.isFocused())
						{
							std::string playerName = GAME_SETTINGS.PLAYER_NAME_DEFAULT;

							MenuItem<call>::runEditWindow(playerName, font, GAME_SETTINGS.PLAYER_NAME_LENGTH, GAME_SETTINGS.PLAYER_NAME_DEFAULT);
							Application::getInstance().getGame().setPlayerRecord({ playerName, Application::getInstance().getGame().getPlayerRecord().second });
							Application::getInstance().getGame().updateRecords(Application::getInstance().getGame().getPlayerRecord());
						}
						window.close();
					}
				}
			}
			window.clear();

			window.draw(title);
			no.drawMenuItem(window);
			yes.drawMenuItem(window);

			window.display();
		}
	}
}