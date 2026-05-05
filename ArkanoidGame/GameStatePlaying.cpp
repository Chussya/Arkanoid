#include "GameStatePlaying.h"

#include <cassert>
#include <functional>

#include "Game.h"
#include "MenuItem.h"
#include "Application.h"

namespace ArkanoidGame
{
	void GameStatePlayingData::handleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			std::shared_ptr <Platform> ptrPlayer = std::dynamic_pointer_cast<Platform>(gameObjects[0]);
			std::shared_ptr<Shell> ptrShell = std::dynamic_pointer_cast<Shell>(gameObjects[1]);

			ptrPlayer->strikeShell(ptrShell);
		}
		if (event.type == sf::Event::MouseMoved)
		{
			mouseMoveX = static_cast<float>(event.mouseMove.x);
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::B)
			{
				Application::getInstance().getGame().switchGameState(EGameStateType::MainMenu);
			} else if (event.key.code == sf::Keyboard::P)
			{
				Application::getInstance().getGame().pushGameState(EGameStateType::Pause, false);
			}
		}
	}

	void GameStatePlayingData::init()
	{
		// Init fonts
		assert(font.loadFromFile(GAME_SETTINGS.RESOURCES_PATH + "Fonts/arial.ttf"));

		/// Init textures
		//assert(data.appleTexture.loadFromFile(RESOURCES_PATH + "Images/apple.png"));

		/// Init music
		//assert(game.music.openFromFile(RESOURCES_PATH + "Music/play.ogg"));

		//// Music settings
		//game.music.setLoop(true);
		//game.music.setVolume(game.gameSettings.musicLoud);

		//// Play
		//game.music.play();

		//// Init texts
		//InitText(data.scoreText, "SCORES:", data.font, sf::Color::White, 20);

		//InitText(data.pauseNote, "For pause use [P]", data.font, sf::Color::White, 20);
		//SetTextOrigin(data.pauseNote, ETextOrigin::RightTop);

		/// Set shell:

		auto shell = std::make_shared<Shell>();
		shell->setSpeed(GAME_SETTINGS.getShellSpeed());

		auto player = std::make_shared<Platform>(Vector2Df({ static_cast<float>(GAME_SETTINGS.SCREEN_WIDTH_GAME / 2), GAME_SETTINGS.SCREEN_HEIGHT_GAME - (GAME_SETTINGS.PLATFORM_HEIGHT_DEFAULT / 2) }));
		player->attachShell(*shell);

		gameObjects.emplace_back(player);
		gameObjects.emplace_back(shell);

		createBlocks(GAME_SETTINGS.BRICKS_COUNT - 2);

		//game.ptrPlayerScores = &data.numEatenApples;
	}

	void GameStatePlayingData::draw(sf::RenderWindow& window)
	{
		// Game objects
		gameObjects[0]->drawOnWindow(window);
		gameObjects[1]->drawOnWindow(window);

		for (auto& brick : bricks)
		{
			brick->drawOnWindow(window);
		}

		// Texts
		window.draw(scoreText);
		scoreText.setPosition(0, 0);
		window.draw(pauseNote);
		pauseNote.setPosition(static_cast<float>(GAME_SETTINGS.SCREEN_WIDTH_GAME - 1), 0.f);
	}

	void GameStatePlayingData::update(float deltaTime)
	{
		// Update scores:
		//data.scoreText.setString("SCORES: " + std::to_string(data.numEatenApples));
		
		std::shared_ptr <Platform> ptrPlayer = std::dynamic_pointer_cast<Platform>(gameObjects[0]);
		std::shared_ptr<Shell> ptrShell = std::dynamic_pointer_cast<Shell>(gameObjects[1]);

		// Update game objects

		gameObjects[0]->update(mouseMoveX);
		gameObjects[1]->update(deltaTime);

		for (auto& brick : bricks)
		{
			brick->update(deltaTime);
		}

		// Check shell reflection
		if (ptrShell->checkState(Shell::EShellState::Striked))
		{
			// Platform reflection
			ptrPlayer->checkCollision(ptrShell);

			// Bricks reflection
			for (auto& brick : bricks)
			{
				if (!brick->isHit() && brick->checkCollision(ptrShell))
				{
					break;
				}
			}
		} else if (ptrShell->checkState(Shell::EShellState::Fallen))
		{
			ptrPlayer->attachShell(*ptrShell);
		}
	}

	void GameStatePlayingData::createBlocks(const int count)
	{
		Vector2Df pos = { 0.f, 200.f };

		for (int i = 0; i < count; ++i)
		{
			bricks.emplace_back(std::make_shared<Brick>(Brick(pos)));
			pos.x += GAME_SETTINGS.BRICK_WIDTH_DEFAULT + 10;
		}
	}
}