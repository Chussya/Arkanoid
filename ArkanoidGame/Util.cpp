#include "Util.h"

namespace ArkanoidGame
{
	void Util::UGraphic::initText(sf::Text& text, std::string s, const sf::Font& font, const sf::Color colorText, const unsigned int charSize)
	{
		text.setFont(font);
		text.setFillColor(colorText);
		text.setString(s);
		text.setCharacterSize(charSize);
	}

	void Util::UGraphic::initText(sf::Text& text, std::string s, const sf::Font& font, const sf::Color colorText, const unsigned int charSize, const Vector2Df pos)
	{
		text.setFont(font);
		text.setFillColor(colorText);
		text.setString(s);
		text.setCharacterSize(charSize);
		text.setPosition({ pos.x, pos.y });
	}

	void Util::UGraphic::initSprite(sf::Sprite& sprite, float desiredWidth, float desiredHeight, const sf::Texture& texture)
	{
		sprite.setTexture(texture);
		setSpriteSize(sprite, desiredWidth, desiredHeight);
		setItemOrigin(sprite, 0.5f, 0.5f);
	}

	void Util::UGraphic::drawSprite(const sf::Sprite& sprite, sf::RenderWindow& window)
	{
		window.draw(sprite);
	}

	void Util::UGraphic::setSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
	{
		sf::FloatRect spriteRect = sprite.getGlobalBounds();
		sf::Vector2f scale = { desiredWidth / spriteRect.width, desiredHeight / spriteRect.height };
		sprite.setScale(scale);
	}
}