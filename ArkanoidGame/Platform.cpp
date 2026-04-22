#include "Platform.h"

#include "Shell.h"
#include "Vector2D.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
	Platform::Platform() {}

	Platform::~Platform() {}

	void Platform::setStartPosition()
	{
		pos = { static_cast<float>(GAME_SETTINGS.SCREEN_WIDTH_GAME / 2), GAME_SETTINGS.SCREEN_HEIGHT_GAME - (platform.getSize().y / 2) };

		platform.setPosition(convert<sf::Vector2f>(pos));
	}

	Vector2Df Platform::getSize()
	{
		return convert<Vector2Df>(platform.getSize());
	}

	void Platform::strikeShell(Shell& shell)
	{
		if (!shell.isActive())
		{
			shell.strike();
		}
	}

	void Platform::attachShell(Shell& shell)
	{
		shell.memorisePlatformPos(pos);
	}

	void Platform::init()
	{
		platform.setSize({ GAME_SETTINGS.PLATFORM_WIDTH_DEFAULT, GAME_SETTINGS.PLATFORM_HEIGHT_DEFAULT });
		platform.setFillColor(sf::Color::Green);
		platform.setOrigin(GAME_SETTINGS.PLATFORM_WIDTH_DEFAULT / 2.f, GAME_SETTINGS.PLATFORM_HEIGHT_DEFAULT / 2.f);
	}

	void Platform::move(const float x)
	{
		pos = { x, platform.getPosition().y };

		platform.setPosition(convert<sf::Vector2f>(pos));
	}

	void Platform::drawOnWindow(sf::RenderWindow& window)
	{
		window.draw(platform);
	}
}