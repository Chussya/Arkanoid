#include "MenuItem.h"

#include "GameSettings.h"

namespace ArkanoidGame
{
	void editElement(std::string& playerName, sf::Font& font)
	{
		sf::RenderWindow window(sf::VideoMode(GAME_SETTINGS.SCREEN_WIDTH_EDIT, GAME_SETTINGS.SCREEN_HEIGHT_EDIT), "Editor");

		sf::Text text;
		Util::UGraphic::initText(text, playerName, font, sf::Color::White, 20);
		sf::String s = text.getString();

		Util::UGraphic::setItemOrigin(text, 0.5f, 0.5f);
		text.setPosition(GAME_SETTINGS.SCREEN_WIDTH_EDIT / 2.f, GAME_SETTINGS.SCREEN_HEIGHT_EDIT / 2.f);

		window.display();

		bool isFinished{ false };

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter)
				{
					window.close();
				}
				if (event.type == sf::Event::TextEntered)
				{
					if (event.text.unicode < 128)
					{
						if (event.text.unicode == '\b')
						{
							if (!s.isEmpty())
								s.erase(s.getSize() - 1);
						} else if (event.text.unicode == 13)
						{
							if (s.isEmpty())
							{
								playerName = GAME_SETTINGS.PLAYER_NAME_DEFAULT;
							} else
							{
								playerName = s;
							}
						} else
						{
							if (s.getSize() < GAME_SETTINGS.PLAYER_NAME_LENGTH)
							{
								s += event.text.unicode;
							}
						}
						text.setString(s);
					}
					Util::UGraphic::setItemOrigin(text, 0.5f, 0.5f);
					text.setPosition(GAME_SETTINGS.SCREEN_WIDTH_EDIT / 2.f, GAME_SETTINGS.SCREEN_HEIGHT_EDIT / 2.f);
				}
			}
			window.clear();
			window.draw(text);
			window.display();
		}
	}
}
