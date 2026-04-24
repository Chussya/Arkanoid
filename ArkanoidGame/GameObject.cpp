#include "GameObject.h"

#include <cassert>

#include "Util.h"

namespace ArkanoidGame
{
	GameObject::GameObject(const std::string& texturePath, const Vector2Df& position, float width, float height) : pos(position)
	{
		assert(texture.loadFromFile(texturePath));

		Util::UGraphic::initSprite(sprite, width, height, texture);
		sprite.setPosition(convert<sf::Vector2f>(position));
	}

	void GameObject::drawOnWindow(sf::RenderWindow& window)
	{
		Util::UGraphic::drawSprite(sprite, window);
	}

	void GameObject::setSpriteOrigin(float originX, float originY)
	{
		Util::UGraphic::setItemOrigin(sprite, originX, originY);
	}
}