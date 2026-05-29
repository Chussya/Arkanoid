#pragma once

#include <functional>
#include <memory>

#include "Collidable.h"
#include "IObservable.h"
#include "GameObject.h"
#include "Vector2D.h"

namespace ArkanoidGame
{
	class Effect : public GameObject, public Collidable, public IObservable
	{
	private:
		bool isActive{ false };
		bool isFallen{ false };
		float duration{ 0 };
		float curentActiveTime{ 0 };
		std::function<void()> activation{ []() {} };
		std::function<void()> deactivation{ []() {} };

		void deactivate();
		void fallen();

	public:
		Effect(const sf::Color& color, std::function<void()>&& bonusActivate, std::function<void()>&& bonusDeactivate, float bonusDuration);

		bool isActivated();
		bool isFalling();
		void create(const Vector2Df& pos);
		void activate();
		void finish();

		// Inherited via GameObject

		void update(const float deltaTime) override;

		// Inherited via Collidable

		bool isCollide(std::shared_ptr<Collidable> collidable) override;
		void onHit() override;
	};
}