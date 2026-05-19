#pragma once
#include <functional>

namespace ArkanoidGame
{
	class Effect
	{
	private:
		bool isActive{ false };
		float duration{ 0 };
		float curentActiveTime{ 0 };
		std::function<void()> activation{ []() {} };
		std::function<void()> deactivation{ []() {} };

		void deactivate();

	public:
		Effect(std::function<void()>&& bonusActivate, std::function<void()>&& bonusDeactivate, float bonusDuration);

		bool isActivated();

		void activate();
		void update(float timeDelta);
	};
}