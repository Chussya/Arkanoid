#pragma once

#include <SFML/Graphics.hpp>

#include "Math.h"
#include "Vector2D.h"
#include "GameObject.h"

namespace ArkanoidGame
{
	class GameSettings;

	class Shell : public GameObject
	{
	private:
		enum class EShellState
		{
			Striked = 1 << 0,
			Fallen = 1 << 1,

			Empty = 0
		};

		// State of shell
		Math::BitMask<EShellState> state;

		// Speed of general vector of move
		float speed;

		float radius;

		// Speed of vectors X and Y
		Vector2Df vectorSpeed;

		// Special pointer of platform's position when shell isn't striked
		Vector2Df* ptrPlatformPos;

		void attachToPlatform();

	public:
		Shell();
		~Shell();

		// Setters

		void setSpeed(const float speed);

		// Interaction

		bool isActive();
		bool isStriked();
		void strike();
		void reflection(const Vector2Df& platformSize);
		void memorisePlatformPos(Vector2Df& platformPos);

		// Standard methods

		void move(const float deltaTime) override;
	};
}