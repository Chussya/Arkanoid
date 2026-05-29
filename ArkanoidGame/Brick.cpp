#include "Brick.h"

#include <cassert>

#include "Shell.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
	Brick::Brick(const Vector2Df& pos, const sf::Color& color) :
		fadeSpeed{ GAME_SETTINGS.getFadeSpeed() },
		Collidable(Collidable::ECollisionShape::Rectangle),
		GameObject(GAME_SETTINGS.RESOURCES_PATH + GAME_SETTINGS.IMG_PATH + "brick.png", pos, GAME_SETTINGS.BRICK_WIDTH_DEFAULT, GAME_SETTINGS.BRICK_HEIGHT_DEFAULT)
	{
		setSpriteOrigin(0.f, 0.f);
		sprite.setColor(color);
	}

	int Brick::getScore()
	{
		return score;
	}

	bool Brick::isAlive()
	{
		return healthPoint > 0;
	}

	bool Brick::isDisappeared()
	{
		return sprite.getColor().a == 0;
	}

	void Brick::disappear(const float deltaTime)
	{
		float alpha = sprite.getColor().a;

		if (alpha > 0)
		{
			alpha -= fadeSpeed * deltaTime;

			if (alpha < 0)
			{
				alpha = 0;
			}
			sprite.setColor(sf::Color(sprite.getColor().r, sprite.getColor().g, sprite.getColor().b, static_cast<sf::Uint8>(alpha)));
		}
	}

	bool Brick::isCollide(std::shared_ptr<Collidable> collidable)
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

		if (distanceSq < sqrNum(radius))
		{
			const Vector2Df leftTopAngle{ rect.left, rect.top };
			const Vector2Df leftBottomAngle{ rect.left, rect.top + rect.height };
			const Vector2Df rightTopAngle{ rect.left + rect.width, rect.top };
			const Vector2Df rightBottomAngle{ rect.left + rect.width, rect.top + rect.height };
			const Vector2Df closePoint{ closestX, closestY };

			if (closePoint == leftTopAngle || closePoint == leftBottomAngle || closePoint == rightTopAngle || closePoint == rightBottomAngle)
			{
				setCollisionSide(ECollisionSide::Angle);
				shell->setCollisionSide(ECollisionSide::Angle);
			} else if (closePoint.x > leftTopAngle.x && closePoint.x < rightTopAngle.x && closePoint.y == leftTopAngle.y)
			{
				setCollisionSide(ECollisionSide::Top);
				shell->setCollisionSide(ECollisionSide::Bottom);
			} else if (closePoint.x > leftBottomAngle.x && closePoint.x < rightBottomAngle.x && closePoint.y == leftBottomAngle.y)
			{
				setCollisionSide(ECollisionSide::Bottom);
				shell->setCollisionSide(ECollisionSide::Top);
			} else if (closePoint.y > leftTopAngle.y && closePoint.y < leftBottomAngle.y && closePoint.x == leftTopAngle.x)
			{
				setCollisionSide(ECollisionSide::Left);
				shell->setCollisionSide(ECollisionSide::Right);
			} else if (closePoint.y > rightTopAngle.y && closePoint.y < rightBottomAngle.y && closePoint.x == leftBottomAngle.x)
			{
				setCollisionSide(ECollisionSide::Right);
				shell->setCollisionSide(ECollisionSide::Left);
			}
			return true;
		}
		return false;
	}

	void Brick::onHit()
	{
		Emit();
	}

	SmoothDestroybleBrick::SmoothDestroybleBrick(const Vector2Df& position, const sf::Color& color) : Brick(position, color), color{ color } { score = 1; }

	void SmoothDestroybleBrick::update(const float deltaTime)
	{
		if (!Brick::isAlive() && !Brick::isDisappeared())
		{
			Brick::disappear(deltaTime);
		}
	}

	bool SmoothDestroybleBrick::isCollide(std::shared_ptr<Collidable> collidable)
	{
		bool isIntersected = Brick::isCollide(collidable);

		if (isIntersected)
		{
			healthPoint = 0;
		}
		return isIntersected;
	}

	UnbreackableBrick::UnbreackableBrick(const Vector2Df& position) : Brick(position, sf::Color(105, 105, 105)) { score = 0; }

	DurableBrick::DurableBrick(const Vector2Df& position, const sf::Color& color) : Brick(position, color), color{ color } { score = 3; healthPoint = 3; }

	void DurableBrick::update(const float deltaTime)
	{
		if (!Brick::isAlive() && !Brick::isDisappeared())
		{
			Brick::disappear(deltaTime);
		} else if (healthPoint == 1)
		{
			sprite.setColor(sf::Color::Green);
		} else if (healthPoint == 2)
		{
			sprite.setColor(sf::Color::Yellow);
		}
	}

	bool DurableBrick::isCollide(std::shared_ptr<Collidable> collidable)
	{
		bool isIntersected = Brick::isCollide(collidable);

		if (isIntersected)
		{
			--healthPoint;
		}
		return isIntersected;
	}
}