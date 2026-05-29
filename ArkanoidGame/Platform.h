#pragma once

#include <memory>

#include "GameObject.h"
#include "Collidable.h"

namespace ArkanoidGame
{
	class Shell;
	class GameSettings;

	class Platform : public GameObject, public Collidable
	{
	private:
		float width{ 0.f };
		Vector2Df pos{ 0.f, 0.f };

	public:
		Platform(Vector2Df pos);
		~Platform();

		/// Interaction

		void attachShell(Shell& shell);
		void strikeShell(std::shared_ptr<Shell> shell);
		void setWidth(const float newWidth);

		/// Inherited via GameObject

		void update(const float x) override;

		/// Inherited via Collidable

		bool checkCollision(std::shared_ptr<Collidable> collidable) override;
		bool isCollide(std::shared_ptr<Collidable> collidable) override;
	};
}