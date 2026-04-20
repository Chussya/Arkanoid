#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"

namespace ArkanoidGame
{
	class Application
	{
	private:
		Game game;
		sf::RenderWindow window;

	public:
		Application(const Application&) = delete;

		Application(const std::string& gameName);
		~Application();

		void Run();
	};

}
