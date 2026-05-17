#include "GameStateLeaderboard.h"

#include <cassert>

#include "Util.h"
#include "Application.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
	void GameStateLeaderboardData::init()
	{
		// Init fonts

		assert(font.loadFromFile(GAME_SETTINGS.FONT_PATH + "arial.ttf"));
		assert(recordsFont.loadFromFile(GAME_SETTINGS.FONT_PATH + "consola.ttf"));

		// Sort records

		RecordsVector records = Application::getInstance().getGame().getSortedRecords();

		if (records.size() > maxRecords)
		{
			records.resize(maxRecords);
		}

		// Leaderboard definition

		std::string tableOfLeaders = "";
		tableOfLeaders.resize(GAME_SETTINGS.ROW_LENGTH, '=');
		tableOfLeaders.push_back('\n');

		for (auto record : records)
		{
			tableOfLeaders.append(Util::UString::stringFormat(record.first, std::to_string(record.second), GAME_SETTINGS.SYM_SEPARATE, GAME_SETTINGS.ROW_LENGTH)).push_back('\n');
		}

		std::string end = "";
		end.resize(GAME_SETTINGS.ROW_LENGTH, '=');
		tableOfLeaders.append(end);

		// Init texts

		Util::UGraphic::initText(title, "LEADERBOARD", font, sf::Color::Blue, 40);
		Util::UGraphic::setItemOrigin(title, 0.5f, 0.5f);

		Util::UGraphic::initText(leaderBoardText, tableOfLeaders, recordsFont, sf::Color::White, 25);
		Util::UGraphic::setItemOrigin(leaderBoardText, 0.5f, 0.5f);
	}

	void GameStateLeaderboardData::handleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::B || event.key.code == sf::Keyboard::Escape)
			{
				Application::getInstance().getGame().exitGame();
			}
		}
	}

	void GameStateLeaderboardData::draw(sf::RenderWindow& window)
	{
		// Set position

		title.setPosition(GAME_SETTINGS.SCREEN_WIDTH_GAME / 2.f, 30.f);
		leaderBoardText.setPosition(GAME_SETTINGS.SCREEN_WIDTH_GAME / 2.f, GAME_SETTINGS.SCREEN_HEIGHT_GAME / 2.f);

		// Draw game over window

		window.draw(title);
		window.draw(leaderBoardText);
	}

	void GameStateLeaderboardData::update(float deltaTime)
	{

	}
}