#pragma once

#include <SFML/Graphics.hpp>

#include "Vector2D.h"

namespace ArkanoidGame
{
	class Shell;

	class Platform
	{
	private:
		Vector2Df pos;
		sf::RectangleShape platform;

	public:
		Platform();
		~Platform();

		void setStartPosition();

		Vector2Df getSize();

		void move(float x);

		void attachShell(Shell& shell);
		void strikeShell(Shell& shell);

		void drawOnWindow(sf::RenderWindow& window);
	};
}