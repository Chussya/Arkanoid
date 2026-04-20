#include "Shell.h"

#include "GameSettings.h"

namespace ArkanoidGame
{
	// Private

	void Shell::reflection(const Vector2Df& platformSize)
	{
		// Side reflection
		if (shell.getPosition().x - shell.getRadius() <= 0.f || shell.getPosition().x + shell.getRadius() >= ArkanoidGame::SCREEN_WIDTH_GAME)
		{
			vectorSpeed.x = -vectorSpeed.x;
		}
		// ceil reflection
		if (shell.getPosition().y - shell.getRadius() <= 0.f)
		{
			vectorSpeed.y = -vectorSpeed.y;
		}
		// platform reflection
		else if (ArkanoidGame::Math::isCircleCollideRect(convert<Vector2Df>(shell.getPosition()), shell.getRadius(), *ptrPlatformPos, PLATFORM_WIDTH_DEFAULT, PLATFORM_HEIGHT_DEFAULT))
		{
			vectorSpeed.x = speed * ((shell.getPosition().x - ptrPlatformPos->x) / (platformSize.x / 2));
			vectorSpeed.y = -vectorSpeed.y;
		}
		// Shell fell
		else if (shell.getPosition().y + shell.getRadius() >= ArkanoidGame::SCREEN_HEIGHT_GAME)
		{
			state.TurnOffMask(EShellState::Striked);
			attachToPlatform();
		}
	}

	void Shell::attachToPlatform()
	{
		shell.setPosition({ ptrPlatformPos->x, ptrPlatformPos->y - PLATFORM_HEIGHT_DEFAULT });

		vectorSpeed.x = 0;
		vectorSpeed.y = 0;
	}

	// Public

	Shell::Shell() :
		state{ EShellState::Empty }, ptrPlatformPos{ nullptr }, speed{ 0.f }
	{
		shell.setRadius(ArkanoidGame::BALL_RADIUS_DEFAULT);
		shell.setFillColor(sf::Color::Red);
		shell.setOrigin(ArkanoidGame::BALL_RADIUS_DEFAULT, ArkanoidGame::BALL_RADIUS_DEFAULT);
	}

	Shell::~Shell()
	{
		delete ptrPlatformPos;
	}

	void Shell::setSpeed(const float speed)
	{
		this->speed = speed;
	}

	void Shell::strike()
	{
		this->state.TurnOnMask(EShellState::Striked);
		vectorSpeed.y = -speed;
	}

	void Shell::memorisePlatformPos(Vector2Df& pos)
	{
		this->ptrPlatformPos = &pos;
		attachToPlatform();
	}

	void Shell::move(const Vector2Df& platformSize, const float deltaTime)
	{
		if (state.IsBitMaskOn(EShellState::Striked))
		{
			reflection(platformSize);

			if (!state.IsBitMaskOn(EShellState::Fallen))
			{
				shell.setPosition(shell.getPosition().x + vectorSpeed.x * deltaTime, shell.getPosition().y + vectorSpeed.y * deltaTime);
			}
		} else
		{
			shell.setPosition({ ptrPlatformPos->x, shell.getPosition().y });
		}
	}

	bool Shell::isActive()
	{
		return !state.IsBitMaskOn(EShellState::Fallen) && state.IsBitMaskOn(EShellState::Striked);
	}

	void Shell::drawOnWindow(sf::RenderWindow& window)
	{
		window.draw(shell);
	}
}