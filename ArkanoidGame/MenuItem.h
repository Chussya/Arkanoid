#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <list>

#include "Util.h"

namespace ArkanoidGame
{
	template<class F>
	class MenuItem
	{
	private:
		bool focused{ false };
		sf::Text text;
		F onClickEvent;

	public:
		// Constructors and Destructors

		MenuItem() = default;
		~MenuItem() = default;

		// Getters

		std::string getButtonName()
		{
			return text.getString();
		}

		// Operators

		bool operator==(const MenuItem<F>& menuItem)
		{
			return this->text.getString() == menuItem.text.getString();
		}

		// Init methods

		void initMenuItem(const std::string string, const sf::Font& font, const unsigned int charSize, F onClickEvent)
		{
			Util::UGraphic::initText(text, string, font, sf::Color::White, charSize);
			text.setOutlineColor(sf::Color::Green);
			this->onClickEvent = onClickEvent;
		}

		// Run event after click

		void clickEvent()
		{
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

		void editElement(std::string& playerName, sf::Font& font);
	};

	using call = std::function<void()>;
	using active = std::list<MenuItem<call>>::iterator;
}