#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <list>

#include "Util.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
	template<class F>
	class MenuItem
	{
	private:
		bool focused{ false };
		bool pressed{ false };
		sf::Text text;
		F onClickEvent;

	public:
		// Constructors and Destructors

		MenuItem() = default;
		~MenuItem() = default;

		// Getters

		bool isPressed()
		{
			return pressed;
		}

		bool isFocused()
		{
			return focused;
		}

		std::string getButtonName()
		{
			return text.getString();
		}

		// Setters

		void setPressed(bool pressed)
		{
			this->pressed = pressed;
		}

		// Operators

		bool operator==(const MenuItem<F>& menuItem)
		{
			return this->text.getString() == menuItem.text.getString();
		}

		// Init methods

		void initMenuItem(const std::string string, const sf::Font& font, const unsigned int charSize, F onClickEvent = [](){})
		{
			Util::UGraphic::initText(text, string, font, sf::Color::White, charSize);
			text.setOutlineColor(sf::Color::Green);
			this->onClickEvent = onClickEvent;
		}

		// Run event after click

		void clickEvent()
		{
			pressed = !pressed;

			onClickEvent();
		}

		// Visual methods

		void setItemOrigin(const float xOrigin, const float yOrigin)
		{
			Util::UGraphic::setItemOrigin(text, xOrigin, yOrigin);
		}

		void setItemPosition(const float x, const float y)
		{
			text.setPosition(x, y);
		}

		void drawMenuItem(sf::RenderWindow& window)
		{
			window.draw(text);
		}

		void onFocus()
		{
			focused = true;

			text.setOutlineThickness(2);
		}

		void lostFocus()
		{
			focused = false;

			text.setOutlineThickness(0);
		}

		static void runEditWindow(std::string& str, sf::Font& font, const int length, const std::string defaultStr)
		{
			sf::RenderWindow window(sf::VideoMode(GAME_SETTINGS.SCREEN_WIDTH_EDIT, GAME_SETTINGS.SCREEN_HEIGHT_EDIT), "Editor");

			sf::Text text;
			Util::UGraphic::initText(text, str, font, sf::Color::White, 20);
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
									str = defaultStr;
								} else
								{
									str = s;
								}
							} else
							{
								if (s.getSize() < length)
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
	};

	using call = std::function<void()>;
	using active = std::list<MenuItem<call>>::iterator;
	using activeRow = std::list<std::pair<MenuItem<call>, sf::RectangleShape>>::iterator;
}