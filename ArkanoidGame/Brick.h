#pragma once

#include <memory>

#include "Math.h"
#include "Collidable.h"
#include "IObservable.h"
#include "GameObject.h"

namespace ArkanoidGame
{
	class Shell;
	class GameSettings;

	class Brick : public GameObject, public Collidable, public IObservable
	{
	protected:
		const float fadeSpeed{ 0.f };
		int score{ 0 };
		int healthPoint{ 1 };

	public:
		Brick(const Vector2Df& pos, const sf::Color& color);
		~Brick() = default;

		// Getters

		int getScore();

		// Interaction

		bool isAlive();
		bool isDisappeared();

		void disappear(const float deltaTime);

		// Inherited via GameObject

		void update(const float deltaTime) override {}

		// Inherited via Collidable

		bool isCollide(std::shared_ptr<Collidable> collidable) override;
		void onHit() override;
	};

	class SmoothDestroybleBrick : public Brick
	{
	protected:
		sf::Color color;

	public:
		SmoothDestroybleBrick(const Vector2Df& position, const sf::Color& color = sf::Color::Green);
		~SmoothDestroybleBrick() = default;

		// Inherited via GameObject

		void update(const float deltaTime) override;

		// Inherited via Collidable

		bool isCollide(std::shared_ptr<Collidable> collidable) override;
	};

	class UnbreackableBrick : public Brick
	{
	public:
		UnbreackableBrick(const Vector2Df& position);

		void update(float) override {}
	};

	class DurableBrick : public Brick
	{
	protected:
		sf::Color color;

	public:
		DurableBrick(const Vector2Df& position, const sf::Color& color = sf::Color::Magenta);
		~DurableBrick() = default;

		// Inherited via GameObject

		void update(const float deltaTime) override;

		// Inherited via Collidable

		bool isCollide(std::shared_ptr<Collidable> collidable) override;
	};
}