#include "Application.h"

#include <cstdlib>

namespace ArkanoidGame
{
	Application::Application() : game(),
		window(sf::VideoMode(GAME_SETTINGS.SCREEN_WIDTH_GAME, GAME_SETTINGS.SCREEN_HEIGHT_GAME), "Arkanoid Game")
	{
		// Init random number generator

		unsigned int seed = (unsigned int)time(nullptr);
		srand(seed);

		window.setMouseCursorGrabbed(true);
		window.setMouseCursorVisible(false);
	}

	Game& Application::getGame()
	{
		return game;
	}

	void Application::run()
	{
		// Init game clock

		sf::Clock gameClock;

		// Game loop

		while (window.isOpen())
		{

			float startTime = gameClock.getElapsedTime().asSeconds();


			if (!window.isOpen())
			{
				break;
			}
			game.updateGame(GAME_SETTINGS.TIME_PER_FRAME, window);


			float endTime = gameClock.getElapsedTime().asSeconds();
			float deltaTime = endTime - startTime;
			if (deltaTime < GAME_SETTINGS.TIME_PER_FRAME)
			{
				// Reduce framerate to not spam CPU and GPU
				sf::sleep(sf::seconds(GAME_SETTINGS.TIME_PER_FRAME - deltaTime));
			}
		}
	}

	Application& Application::getInstance()
	{
		static Application instance;
		
		return instance;
	}
}