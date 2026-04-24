#include "Shell.h"

#include "GameSettings.h"

namespace ArkanoidGame
{
	// Private

	void Shell::attachToPlatform()
	{
		sprite.setPosition({ ptrPlatformPos->x, ptrPlatformPos->y - GAME_SETTINGS.PLATFORM_HEIGHT_DEFAULT });

		vectorSpeed.x = 0;
		vectorSpeed.y = 0;
	}

	// Public

	Shell::Shell() :
		state{ EShellState::Empty },
		ptrPlatformPos{ nullptr },
		speed{ 0.f },
		GameObject(GAME_SETTINGS.RESOURCES_PATH + GAME_SETTINGS.IMG_PATH + "shell.png", { 0.f, 0.f }, GAME_SETTINGS.BALL_RADIUS_DEFAULT * 2, GAME_SETTINGS.BALL_RADIUS_DEFAULT * 2)
	{
		radius = GAME_SETTINGS.BALL_RADIUS_DEFAULT;
		setSpriteOrigin(0.5f, 0.5f);
	}

	Shell::~Shell() {}

	void Shell::setSpeed(const float speed)
	{
		this->speed = speed;
	}

	bool Shell::isActive()
	{
		return !state.IsBitMaskOn(EShellState::Fallen) && state.IsBitMaskOn(EShellState::Striked);
	}

	bool Shell::isStriked()
	{
		return state.IsBitMaskOn(EShellState::Striked);
	}

	void Shell::strike()
	{
		state.TurnOnMask(EShellState::Striked);
		vectorSpeed.y = -speed;
	}

	void Shell::reflection(const Vector2Df& platformSize)
	{
		if (isStriked())
		{
			// Side reflection
			if (sprite.getPosition().x - radius <= 0.f || sprite.getPosition().x + radius >= GAME_SETTINGS.SCREEN_WIDTH_GAME)
			{
				vectorSpeed.x = -vectorSpeed.x;
			}
			// ceil reflection
			if (sprite.getPosition().y - radius <= 0.f)
			{
				vectorSpeed.y = -vectorSpeed.y;
			}
			// platform reflection
			else if (ArkanoidGame::Math::isCircleCollideRect(convert<Vector2Df>(sprite.getPosition()), radius, *ptrPlatformPos, platformSize.x, platformSize.y))
			{
				vectorSpeed.x = speed * ((sprite.getPosition().x - ptrPlatformPos->x) / (platformSize.x / 2));
				vectorSpeed.y = -vectorSpeed.y;
			}
			// Shell fell
			else if (sprite.getPosition().y + radius >= GAME_SETTINGS.SCREEN_HEIGHT_GAME)
			{
				state.TurnOffMask(EShellState::Striked);
				attachToPlatform();
			}
		}
	}

	void Shell::memorisePlatformPos(Vector2Df& pos)
	{
		ptrPlatformPos = &pos;
		attachToPlatform();
	}

	void Shell::move(const float deltaTime)
	{
		if (state.IsBitMaskOn(EShellState::Striked))
		{
			if (!state.IsBitMaskOn(EShellState::Fallen))
			{
				sprite.setPosition(sprite.getPosition().x + vectorSpeed.x * deltaTime, sprite.getPosition().y + vectorSpeed.y * deltaTime);
			}
		} else
		{
			sprite.setPosition({ ptrPlatformPos->x, sprite.getPosition().y });
		}
	}
}