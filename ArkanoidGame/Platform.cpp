#include "Platform.h"

#include "Shell.h"
#include "Vector2D.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
	Platform::Platform()
	{
		platform.setSize({ ArkanoidGame::PLATFORM_WIDTH_DEFAULT, ArkanoidGame::PLATFORM_HEIGHT_DEFAULT });
		platform.setFillColor(sf::Color::Green);
		platform.setOrigin(ArkanoidGame::PLATFORM_WIDTH_DEFAULT / 2.f, ArkanoidGame::PLATFORM_HEIGHT_DEFAULT / 2.f);
	}

	Platform::~Platform() {}

	void Platform::setStartPosition(int windowWidth, int windowHeight)
	{
		pos = { static_cast<float>(windowWidth / 2), static_cast<float>(windowHeight - (platform.getSize().y / 2)) };

		platform.setPosition(convert<sf::Vector2f>(pos));
	}

	Vector2Df Platform::getSize()
	{
		return convert<Vector2Df>(platform.getSize());
	}

	void Platform::move(float x)
	{
		pos = {x, platform.getPosition().y };

		platform.setPosition(convert<sf::Vector2f>(pos));
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

	void Platform::drawOnWindow(sf::RenderWindow& window)
	{
		window.draw(platform);
	}
}