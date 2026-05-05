#pragma once

#include "Collidable.h"
#include "GameObject.h"

namespace ArkanoidGame
{
	class Shell;
	class GameSettings;

	class Brick : public GameObject, public Collidable
	{
	private:
		const float fadeSpeed{ 0.f };
		bool hit{ false };

	public:
		Brick(Vector2Df pos);
		~Brick() = default;

		/// Interaction

		bool isHit();

		/// Inherited via GameObject

		void update(const float deltaTime) override;

		/// Inherited via Collidable

		bool isCollide(std::shared_ptr<Collidable> collidable) override;
	};
}