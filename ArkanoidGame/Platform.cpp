#include "Platform.h"

#include "Shell.h"
#include "Vector2D.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
	Platform::Platform(Vector2Df pos) : GameObject(GAME_SETTINGS.RESOURCES_PATH + GAME_SETTINGS.IMG_PATH + "platform.png", pos, GAME_SETTINGS.PLATFORM_WIDTH_DEFAULT, GAME_SETTINGS.PLATFORM_HEIGHT_DEFAULT)
	{
		setSpriteOrigin(0.5f, 0.5f);
	}

	Platform::~Platform() {}

	Vector2Df Platform::getSize()
	{
		return { sprite.getGlobalBounds().width, sprite.getGlobalBounds().height };
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

	void Platform::move(const float x)
	{
		pos = { x, sprite.getPosition().y };

		sprite.setPosition(convert<sf::Vector2f>(pos));
	}
}