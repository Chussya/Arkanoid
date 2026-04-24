#pragma once

#include <SFML/Graphics.hpp>

#include "Vector2D.h"

namespace ArkanoidGame
{
	class GameObject
	{
	protected:
		sf::Sprite sprite;
		sf::Texture texture;
		Vector2Df pos;

	public:
		GameObject(const std::string& textureId, const Vector2Df& position, float width, float height);
		virtual ~GameObject() = default;

		// Standard virtual methods

		virtual void move(const float) = 0;
		virtual void drawOnWindow(sf::RenderWindow&);

		// General methods

		virtual void setSpriteOrigin(float originX, float originY);
	};
}