#pragma once

#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "Vector2D.h"

namespace ArkanoidGame
{
	class Shell;
	class GameSettings;

	class Platform : public GameObject
	{
	private:

	public:
		Platform(Vector2Df pos);
		~Platform();

		// Interaction

		Vector2Df getSize();

		void attachShell(Shell& shell);
		void strikeShell(Shell& shell);

		// Standard methods

		void move(const float x) override;
	};
}