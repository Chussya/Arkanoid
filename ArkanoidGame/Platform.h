#pragma once

#include <SFML/Graphics.hpp>

#include "Vector2D.h"

namespace ArkanoidGame
{
	class Shell;
	class GameSettings;

	class Platform
	{
	private:
		Vector2Df pos;
		sf::RectangleShape platform;

	public:
		Platform();
		~Platform();

		// Setters

		void setStartPosition(float screenWidth, float sreenHeight);

		// Interaction

		Vector2Df getSize();

		void attachShell(Shell& shell);
		void strikeShell(Shell& shell);

		// Standard methods

		void init(const GameSettings& gameSettings);
		void move(const float x);
		void drawOnWindow(sf::RenderWindow& window);
	};
}