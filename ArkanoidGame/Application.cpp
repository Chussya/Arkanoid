#include "Application.h"

#include <cstdlib>

namespace ArkanoidGame
{
	Application::Application(const std::string& gameName) : game(),
		window(sf::VideoMode(GAME_SETTINGS.SCREEN_WIDTH_GAME, GAME_SETTINGS.SCREEN_HEIGHT_GAME), "Arkanoid")
	{
		// Init random number generator
		unsigned int seed = (unsigned int)time(nullptr); // Get current time as seed. You can also use any other number to fix randomization
		srand(seed);

		window.setMouseCursorGrabbed(true);
		window.setMouseCursorVisible(false);
	}

	Application::~Application()
	{
		game.~Game();
	}

	void Application::Run()
	{
		// Init game clock
		sf::Clock gameClock;

		// Game loop
		while (window.isOpen())
		{

			float startTime = gameClock.getElapsedTime().asSeconds();

			game.handleWindowEvents(window);

			if (!window.isOpen())
			{
				break;
			}

			if (game.update(GAME_SETTINGS.TIME_PER_FRAME))
			{
				// Draw everything here
				// Clear the window first
				window.clear();

				game.draw(window);

				// End the current frame, display window contents on screen
				window.display();
			} else
			{
				window.close();
			}

			float endTime = gameClock.getElapsedTime().asSeconds();
			float deltaTime = endTime - startTime;
			if (deltaTime < GAME_SETTINGS.TIME_PER_FRAME)
			{
				// Reduce framerate to not spam CPU and GPU
				sf::sleep(sf::seconds(GAME_SETTINGS.TIME_PER_FRAME - deltaTime));
			}
		}
	}

}