#include "Effect.h"

namespace ArkanoidGame
{
	// Private

	void Effect::deactivate()
	{
		isActive = false;
		curentActiveTime = 0;
		if (deactivation)
			deactivation();
	}

	// Public

	Effect::Effect(std::function<void()>&& effectStart, std::function<void()>&& effectEnd, float bonusDuration) :
		activation{ std::move(effectStart) },
		deactivation{ std::move(effectEnd) },
		duration{ bonusDuration }
	{}

	bool Effect::isActivated()
	{
		return isActive;
	}

	void Effect::activate()
	{
		isActive = true;

		if (activation)
		{
			activation();
		}
	}

	void Effect::update(float deltaTime)
	{
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
}