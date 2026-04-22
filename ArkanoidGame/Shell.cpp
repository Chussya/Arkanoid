#include "Shell.h"

#include "GameSettings.h"

namespace ArkanoidGame
{
	// Private

	void Shell::attachToPlatform()
	{
		shell.setPosition({ ptrPlatformPos->x, ptrPlatformPos->y - GAME_SETTINGS.PLATFORM_HEIGHT_DEFAULT });

		vectorSpeed.x = 0;
		vectorSpeed.y = 0;
	}

	// Public

	Shell::Shell() : state{ EShellState::Empty }, ptrPlatformPos{ nullptr }, speed{ 0.f } {}

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
			if (shell.getPosition().x - shell.getRadius() <= 0.f || shell.getPosition().x + shell.getRadius() >= GAME_SETTINGS.SCREEN_WIDTH_GAME)
			{
				vectorSpeed.x = -vectorSpeed.x;
			}
			// ceil reflection
			if (shell.getPosition().y - shell.getRadius() <= 0.f)
			{
				vectorSpeed.y = -vectorSpeed.y;
			}
			// platform reflection
			else if (ArkanoidGame::Math::isCircleCollideRect(convert<Vector2Df>(shell.getPosition()), shell.getRadius(), *ptrPlatformPos, platformSize.x, platformSize.y))
			{
				vectorSpeed.x = speed * ((shell.getPosition().x - ptrPlatformPos->x) / (platformSize.x / 2));
				vectorSpeed.y = -vectorSpeed.y;
			}
			// Shell fell
			else if (shell.getPosition().y + shell.getRadius() >= GAME_SETTINGS.SCREEN_HEIGHT_GAME)
			{
				state.TurnOffMask(EShellState::Striked);
				attachToPlatform();
			}
		}
	}

	void Shell::memorisePlatformPos(Vector2Df& pos)
	{
		this->ptrPlatformPos = &pos;
		attachToPlatform();
	}

	void Shell::init()
	{
		shell.setRadius(GAME_SETTINGS.BALL_RADIUS_DEFAULT);
		shell.setFillColor(sf::Color::Red);
		shell.setOrigin(GAME_SETTINGS.BALL_RADIUS_DEFAULT, GAME_SETTINGS.BALL_RADIUS_DEFAULT);
	}

	void Shell::move(const float deltaTime)
	{
		if (state.IsBitMaskOn(EShellState::Striked))
		{
			if (!state.IsBitMaskOn(EShellState::Fallen))
			{
				shell.setPosition(shell.getPosition().x + vectorSpeed.x * deltaTime, shell.getPosition().y + vectorSpeed.y * deltaTime);
			}
		} else
		{
			shell.setPosition({ ptrPlatformPos->x, shell.getPosition().y });
		}
	}

	void Shell::drawOnWindow(sf::RenderWindow& window)
	{
		window.draw(shell);
	}
}