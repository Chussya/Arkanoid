#include "Platform.h"

#include "Shell.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
	Platform::Platform(Vector2Df pos) :
		width{ GAME_SETTINGS.PLATFORM_WIDTH_DEFAULT },
		pos{ pos },
		Collidable(Collidable::ECollisionShape::Rectangle),
		GameObject(GAME_SETTINGS.RESOURCES_PATH + GAME_SETTINGS.IMG_PATH + "platform.png", pos, GAME_SETTINGS.PLATFORM_WIDTH_DEFAULT, GAME_SETTINGS.PLATFORM_HEIGHT_DEFAULT)
	{
		setSpriteOrigin(0.5f, 0.5f);
	}

	Platform::~Platform() {}

	void Platform::strikeShell(std::shared_ptr<Shell> shell)
	{
		if (!shell->checkState(Shell::EShellState::Striked))
		{
			shell->strike();
		}
	}

	void Platform::attachShell(Shell& shell)
	{
		shell.setPlatformData({ &width, &pos });
		shell.attachToPlatform();
	}

	void Platform::update(const float x)
	{
		pos = { x, getPosition().y };

		sprite.setPosition(convert<sf::Vector2f>(pos));
	}

	bool Platform::isCollide(std::shared_ptr<Collidable> collidable)
	{
		auto ball = std::static_pointer_cast<Shell>(collidable);
		if (!ball) return false;

		auto sqrNum = [](float x) { return x * x; };

		const auto rect = sprite.getGlobalBounds();
		const auto ballPos = ball->getPosition();

		bool res{ false };

		if (ballPos.x < rect.left)
		{
			if (sqrNum(ballPos.x - rect.left) + sqrNum(ballPos.y - rect.top) < sqrNum(GAME_SETTINGS.BALL_RADIUS_DEFAULT))
			{
				setCollisionSide(ECollisionSide::Left);
				res = true;
			}
		} else if (ballPos.x > rect.left + rect.width)
		{
			if (sqrNum(ballPos.x - rect.left - rect.width) + sqrNum(ballPos.y - rect.top) < sqrNum(GAME_SETTINGS.BALL_RADIUS_DEFAULT))
			{
				setCollisionSide(ECollisionSide::Right);
				res = true;
			}
		} else if (std::fabs(ballPos.y - rect.top) <= GAME_SETTINGS.BALL_RADIUS_DEFAULT)
		{
			setCollisionSide(ECollisionSide::Top);
			res = true;
		}
		return res;
	}

	bool Platform::checkCollision(std::shared_ptr<Collidable> collidable)
	{
		auto shell = std::static_pointer_cast<Shell>(collidable);

		if (!shell)
			return false;

		if (isCollide(shell))
		{
			shell->collidePlatform(
				getCollisionSide() == ECollisionSide::Right
				? ECollisionSide::Left
				: (getCollisionSide() == ECollisionSide::Left ? ECollisionSide::Right : ECollisionSide::Bottom));

			shell->onHit();
			onHit();
			return true;
		}
		return false;
	}
}