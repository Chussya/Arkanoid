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

	void Platform::setWidth(const float newWidth)
	{
		width = newWidth;
		updateSpriteSize(width, GAME_SETTINGS.PLATFORM_HEIGHT_DEFAULT);
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
		auto shell{ std::static_pointer_cast<Shell>(collidable) };
		if (!shell) return false;

		auto sqrNum = [](float x) { return x * x; };

		const float radius = GAME_SETTINGS.BALL_RADIUS_DEFAULT;
		const auto rect{ sprite.getGlobalBounds() };
		Vector2Df circleCenter(convert<Vector2Df>(shell->getPosition()));

		float closestX = std::max(rect.left, std::min(circleCenter.x, rect.left + rect.width));
		float closestY = std::max(rect.top, std::min(circleCenter.y, rect.top + rect.height));

		sf::Vector2f distanceVec(circleCenter.x - closestX, circleCenter.y - closestY);
		float distanceSq = sqrNum(distanceVec.x) + sqrNum(distanceVec.y);

		return distanceSq < sqrNum(radius);
	}

	bool Platform::checkCollision(std::shared_ptr<Collidable> collidable)
	{
		auto shell = std::static_pointer_cast<Shell>(collidable);

		if (!shell)
			return false;

		if (isCollide(shell))
		{
			shell->collidePlatform(ECollisionSide::Bottom);

			shell->onHit();
			onHit();
			return true;
		}
		return false;
	}
}