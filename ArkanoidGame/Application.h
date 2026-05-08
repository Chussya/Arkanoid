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
		// Constructors & Desctructors

		Application(const Application&) = delete;

		Application();
		~Application() = default;;

		// Getters

		Game& getGame();

		// Other methods

		void run();

	public:
		// Static methods

		static Application& getInstance();
	};

}
