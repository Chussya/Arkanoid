#pragma once

#include <SFML/Graphics.hpp>

#include "Math.h"
//#include "UtilGraphic.h"

namespace ArkanoidGame
{
	template<typename F>
	class MenuItem
	{
	private:
		bool onFocus{ false };
		sf::Text text;
		F callFunc;

	public:
		bool operator==(const MenuItem<F>& menuItem)
		{
			return this.text.getString() == menuItem.text.getString();
		}

		void InitMenuItem(MenuItem<F>& menuItem, const std::string text, const sf::Font& font, const unsigned int charSize, F callFunc)
		{
			InitText(menuItem.text, text, font, sf::Color::White, charSize);
			menuItem.text.setOutlineColor(sf::Color::Green);
			menuItem.callFunc = callFunc;
		}

		void DrawMenuItem(MenuItem<F>& menuItem, sf::RenderWindow& window)
		{
			window.draw(menuItem.text);
		}

		void OnFocus(MenuItem<F>& menuItem)
		{
			menuItem.onFocus = true;

			menuItem.text.setOutlineThickness(2);
		}

		void LostFocus(MenuItem<F>& menuItem)
		{
			menuItem.onFocus = false;

			menuItem.text.setOutlineThickness(0);
		}

		void EditElement(std::string& playerName, sf::Font& font);
	};
}