#pragma once

#include <SFML/Graphics.hpp>

class GameStateData
{
public:
	virtual ~GameStateData() = default;

	virtual void init() = 0;
	virtual void handleWindowEvent(const sf::Event&) = 0;
	virtual void update(float) = 0;
	virtual void draw(sf::RenderWindow&) = 0;
};