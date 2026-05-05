#include "Brick.h"

#include <cassert>

#include "GameSettings.h"

namespace ArkanoidGame
{
	Brick::Brick(Vector2Df pos) :
		fadeSpeed{ GAME_SETTINGS.getFadeSpeed() },
		Collidable(Collidable::ECollisionShape::Rectangle),
		GameObject(GAME_SETTINGS.RESOURCES_PATH + GAME_SETTINGS.IMG_PATH + "brick.png", pos, GAME_SETTINGS.BRICK_WIDTH_DEFAULT, GAME_SETTINGS.BRICK_HEIGHT_DEFAULT)
	{
		setSpriteOrigin(0.f, 0.f);
	}

	bool Brick::isHit()
	{
		return hit;
	}

	void Brick::update(const float deltaTime)
	{
		if (hit)
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
	}

	bool Brick::isCollide(std::shared_ptr<Collidable> collidable)
	{
		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidable);
		assert(gameObject);

		sf::FloatRect intersection;

		bool isIntersected = getRect().intersects(gameObject->getRect(), intersection);

		if (isIntersected)
		{
			float intersectionCenterX{ intersection.left + (intersection.width / 2) };
			float intersectionCenterY{ intersection.top + (intersection.height / 2) };

			float dxLeft{ intersectionCenterX - getRect().left }, dxRight{ (getRect().left + getRect().width) - intersectionCenterX };
			float dyTop{ intersectionCenterY - getRect().top }, dyBottom{ (getRect().top + getRect().height) - intersectionCenterY };

			if (dyTop < dyBottom && dyTop < dxLeft && dyTop < dxRight)
			{
				setCollisionSide(ECollisionSide::Top);
				collidable->setCollisionSide(ECollisionSide::Bottom);
			} else if (dyTop > dyBottom && dyBottom < dxLeft && dyBottom < dxRight)
			{
				setCollisionSide(ECollisionSide::Bottom);
				collidable->setCollisionSide(ECollisionSide::Top);
			} else if (dxLeft < dxRight && dxLeft < dyTop && dxLeft < dyBottom)
			{
				setCollisionSide(ECollisionSide::Left);
				collidable->setCollisionSide(ECollisionSide::Right);
			} else if (dxLeft > dxRight && dxRight < dyTop && dxRight < dyBottom)
			{
				setCollisionSide(ECollisionSide::Right);
				collidable->setCollisionSide(ECollisionSide::Left);
			} else
			{
				setCollisionSide(ECollisionSide::Angle);
				collidable->setCollisionSide(ECollisionSide::Angle);
			}
		}
		return isIntersected;
	}
}