#pragma once

#include "Math.h"
#include "Collidable.h"
#include "GameObject.h"

namespace ArkanoidGame
{
	class Shell;
	class GameSettings;

	class Brick : public GameObject, public Collidable
	{
	public:
		enum class EBrickState
		{
			Disappearing = 1,
			Disappeared = 2,

			Empty = 0
		};

	private:
		Math::BitMask<EBrickState> state;
		const float fadeSpeed{ 0.f };

	public:
		Brick(Vector2Df pos);
		~Brick() = default;

		/// Interaction

		bool isAlive();

		/// Inherited via GameObject

		void update(const float deltaTime) override;

		/// Inherited via Collidable

		bool isCollide(std::shared_ptr<Collidable> collidable) override;
	};
}