#include "GameStatePlaying.h"

#include <cassert>
#include <functional>

#include "Game.h"
#include "MenuItem.h"
#include "Application.h"

namespace ArkanoidGame
{
	GameStatePlayingData::GameStatePlayingData()
	{
		score = Application::getInstance().getGame().getPlayerRecord().second;
	}

	GameStatePlayingData::~GameStatePlayingData()
	{
		Application::getInstance().getGame().setPlayerRecord({ Application::getInstance().getGame().getPlayerRecord().first, score });
	}

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
		assert(font.loadFromFile(GAME_SETTINGS.FONT_PATH + "arial.ttf"));

		// Init texts
		Util::UGraphic::initText(scoreText, "SCORES: " + std::to_string(score), font, sf::Color::White, 20);

		Util::UGraphic::initText(pauseNote, "For pause use [P]", font, sf::Color::White, 20);
		Util::UGraphic::setItemOrigin(pauseNote, 1.f, 0.f);

		/// Set shell:

		auto shell = std::make_shared<Shell>();
		shell->setSpeed(GAME_SETTINGS.getShellSpeed());

		auto player = std::make_shared<Platform>(Vector2Df({ static_cast<float>(GAME_SETTINGS.SCREEN_WIDTH_GAME / 2), GAME_SETTINGS.SCREEN_HEIGHT_GAME - (GAME_SETTINGS.PLATFORM_HEIGHT_DEFAULT / 2) }));
		player->attachShell(*shell);

		gameObjects.emplace_back(player);
		gameObjects.emplace_back(shell);

		// Init level:
		createLevel();
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
		scoreText.setString("SCORES: " + std::to_string(score));
		
		std::shared_ptr <Platform> ptrPlayer = std::dynamic_pointer_cast<Platform>(gameObjects[0]);
		std::shared_ptr<Shell> ptrShell = std::dynamic_pointer_cast<Shell>(gameObjects[1]);

		// Update game objects

		gameObjects[0]->update(mouseMoveX);
		gameObjects[1]->update(deltaTime);

		for (auto& brick : bricks)
		{
			brick->update(deltaTime);
		}

		auto aliveBricks = std::count_if(bricks.begin(), bricks.end(), [](std::shared_ptr<Brick> b) { return b->isAlive() && b->getScore() > 0; });

		if (aliveBricks == 0)
		{
			Application::getInstance().getGame().getLevelManager().nextLevel();
			Application::getInstance().getGame().pushGameState(EGameStateType::Victory, false);
			Application::getInstance().getGame().getAudio().playFullSound(AudioManager::ESoundEffect::Victory);
		}
		// Check shell reflection
		else if (ptrShell->checkState(Shell::EShellState::Striked))
		{
			// Platform reflection
			ptrPlayer->checkCollision(ptrShell);

			// Bricks reflection
			for (auto& brick : bricks)
			{
				if (brick->isAlive() && brick->checkCollision(ptrShell))
				{
					soundHit.setBuffer(Application::getInstance().getGame().getAudio().getSoundBuffer(AudioManager::ESoundEffect::Hit));
					soundHit.setVolume(GAME_SETTINGS.getSoundVolume());
					soundHit.play();

					if (!brick->isAlive())
					{
						score += brick->getScore();
					}
					break;
				}
			}
		} else if (ptrShell->checkState(Shell::EShellState::Fallen))
		{
			Application::getInstance().getGame().getAudio().playFullSound(AudioManager::ESoundEffect::Death);
			Application::getInstance().getGame().switchGameState(EGameStateType::GameOver);
		}
	}

	void GameStatePlayingData::createLevel()
	{
		float startHeight{ 100.f };
		float startWidth{ 60.f };
		Vector2Df pos = { startWidth, startHeight };
		BricksTemplate arr = Application::getInstance().getGame().getLevelManager().getLevel();

		std::for_each(arr.begin(), arr.end(),
			[&](const BricksRow& row)
			{
				std::for_each(row.begin(), row.end(),
					[&](int element)
					{
						switch (element)
						{
						case 0:
						{
							auto brick = std::make_shared<UnbreackableBrick>(pos);
							bricks.emplace_back(brick);
							break;
						}
						case 1:
						{
							auto brick = std::make_shared<SmoothDestroybleBrick>(pos);
							bricks.emplace_back(brick);
							break;
						}
						case 2:
						{
							auto brick = std::make_shared<DurableBrick>(pos);
							bricks.emplace_back(brick);
							break;
						}
						default:
							break;
						}
						pos.x += GAME_SETTINGS.BRICK_WIDTH_DEFAULT + GAME_SETTINGS.BRICK_SHIFT_WIDTH;
					});
				pos.x = startWidth;
				pos.y += GAME_SETTINGS.BRICK_SHIFT_HEIGHT;
			});
	}
}