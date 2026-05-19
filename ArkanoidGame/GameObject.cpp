#include "GameObject.h"

#include <cassert>

#include "Util.h"

namespace ArkanoidGame
{
	// Public

	GameObject::GameObject(const std::string& texturePath, const Vector2Df& position, float width, float height)
	{
		assert(texture.loadFromFile(texturePath));

		Util::UGraphic::initSprite(sprite, width, height, texture);
		sprite.setPosition(convert<sf::Vector2f>(position));
	}

	void GameObject::drawOnWindow(sf::RenderWindow& window)
	{
		Util::UGraphic::drawSprite(sprite, window);
	}

	Vector2Df GameObject::getPosition() const
	{
		return convert<Vector2Df>(sprite.getPosition());
	}

	sf::FloatRect GameObject::getRect() const
	{
		return sprite.getGlobalBounds();
	}

	void GameObject::setSpriteOrigin(const float originX, const float originY)
	{
		Util::UGraphic::setItemOrigin(sprite, originX, originY);
	}

	void GameObject::updateSpriteSize(const float width, const float height)
	{
		const float scaleX{ width / sprite.getGlobalBounds().width };
		const float scaleY{ height / sprite.getGlobalBounds().height };

		sprite.scale(scaleX, scaleY);
	}
}