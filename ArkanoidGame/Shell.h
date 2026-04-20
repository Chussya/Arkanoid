#pragma once

#include <SFML/Graphics.hpp>

#include "Math.h"
#include "Vector2D.h"

namespace ArkanoidGame
{
	class Shell
	{
	private:
		enum class EShellState
		{
			Striked = 1 << 0,
			Fallen = 1 << 1,

			Empty = 0
		};

	private:
		// State of shell
		Math::BitMask<EShellState> state;

		// Speed of general vector of move
		float speed;

		// Speed of vectors X and Y
		Vector2Df vectorSpeed;

		// Special pointer of platform's position when shell isn't striked
		Vector2Df* ptrPlatformPos;

		// Form of shell
		sf::CircleShape shell;

	private:
		void reflection(const Vector2Df& platformSize);
		void attachToPlatform();

	public:
		Shell();
		~Shell();

		void setSpeed(const float speed);

		void strike();

		void memorisePlatformPos(Vector2Df& platformPos);
		void move(const Vector2Df& platformSize, const float deltaTime);

		bool isActive();

		void drawOnWindow(sf::RenderWindow& window);
	};
}