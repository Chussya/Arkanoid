#include "Effect.h"

#include "Platform.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
	// Private

	void Effect::deactivate()
	{
		isActive = false;
		curentActiveTime = 0;

		if (deactivation)
		{
			deactivation();
		}
	}

	void Effect::fallen()
	{
		isFallen = false;
		sprite.setPosition(-50.f, -50.f);
	}

	// Public

	Effect::Effect(const sf::Color& color, std::function<void()>&& effectStart, std::function<void()>&& effectEnd, float bonusDuration) :
		activation{ std::move(effectStart) },
		deactivation{ std::move(effectEnd) },
		duration{ bonusDuration },
		Collidable(Collidable::ECollisionShape::Rectangle),
		GameObject(GAME_SETTINGS.RESOURCES_PATH + GAME_SETTINGS.IMG_PATH + "effect.png", { -50.f, -50.f }, GAME_SETTINGS.EFFECT_WIDTH, GAME_SETTINGS.EFFECT_HEIGHT)
	{
		sprite.setColor(color);
	}

	bool Effect::isActivated()
	{
		return isActive;
	}

	bool Effect::isFalling()
	{
		return isFallen;
	}

	void Effect::create(const Vector2Df& pos)
	{
		sprite.setPosition(pos.x, pos.y);

		isFallen = true;
	}

	void Effect::activate()
	{
		isActive = true;

		if (activation)
		{
			activation();
		}
	}

	void Effect::finish()
	{
		fallen();
		deactivate();
	}

	void Effect::update(const float deltaTime)
	{
		if (isFallen)
		{
			sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + GAME_SETTINGS.EFFECT_FALL_SPEED * deltaTime);
			return;
		}
		if (!isActive)
		{
			return;
		}
		curentActiveTime += deltaTime;

		if (curentActiveTime >= duration)
		{
			deactivate();
		}
	}
	
	bool Effect::isCollide(std::shared_ptr<Collidable> collidable)
	{
		auto platform{ std::static_pointer_cast<Platform>(collidable) };
		if (!platform) return false;

		// Check window bottom collision
		if (getPosition().y >= GAME_SETTINGS.SCREEN_HEIGHT_GAME)
		{
			finish();
			return false;
		}
		return getRect().intersects(platform->getRect());
	}

	void Effect::onHit()
	{
		fallen();
		Emit();
	}
}