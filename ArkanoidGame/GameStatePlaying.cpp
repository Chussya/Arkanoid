#include "GameStatePlaying.h"

#include <cassert>
#include <functional>

#include "Game.h"
#include "MenuItem.h"
#include "Application.h"

namespace ArkanoidGame
{
	GameStatePlayingData::GameStatePlayingData() : tries { GAME_SETTINGS.TRIES_COUNT }
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
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::getInstance().getGame().exitGame();
			} else if (event.key.code == sf::Keyboard::P)
			{
				Application::getInstance().getGame().pauseGame();
			}
		}
	}

	void GameStatePlayingData::init()
	{
		// Init fonts
		assert(font.loadFromFile(GAME_SETTINGS.FONT_PATH + "arial.ttf"));

		// Factories Init
		brickFactories.emplace(BrickType::Simple, std::make_unique<SimpleBrickFactory>());
		brickFactories.emplace(BrickType::Durable, std::make_unique<DurableBrickFactory>());
		brickFactories.emplace(BrickType::Unbreackable, std::make_unique<UnbreackableBrickFactory>());

		// Init texts
		Util::UGraphic::initText(scoreText, "SCORES: " + std::to_string(score), font, sf::Color::White, 20);
		Util::UGraphic::initText(triesText, "ATTEMPTS LEFT: " + std::to_string(tries), font, sf::Color::Red, 20);
		Util::UGraphic::setItemOrigin(triesText, 0.5f, 0.f);

		Util::UGraphic::initText(pauseNote, "For pause use [P]", font, sf::Color::White, 20);
		Util::UGraphic::setItemOrigin(pauseNote, 1.f, 0.f);

		// Set shell:

		auto shell = std::make_shared<Shell>();
		shell->AddObserver(weak_from_this());

		auto player = std::make_shared<Platform>(Vector2Df({ static_cast<float>(GAME_SETTINGS.SCREEN_WIDTH_GAME / 2), GAME_SETTINGS.SCREEN_HEIGHT_GAME - (GAME_SETTINGS.PLATFORM_HEIGHT_DEFAULT / 2) }));
		player->attachShell(*shell);

		gameObjects.emplace_back(player);
		gameObjects.emplace_back(shell);

		// Init sounds
		soundHit.setBuffer(Application::getInstance().getGame().getAudio().getSoundBuffer(AudioManager::ESoundEffect::Hit));
		soundFail.setBuffer(Application::getInstance().getGame().getAudio().getSoundBuffer(AudioManager::ESoundEffect::Fail));
		soundEffect.setBuffer(Application::getInstance().getGame().getAudio().getSoundBuffer(AudioManager::ESoundEffect::Effect));

		// Init effects

		effects.emplace(EffectType::SlowBall, std::make_shared<Effect>(
			sf::Color::Green,
			[wShell = std::weak_ptr<Shell>(shell), &sound = soundEffect]() {
				auto shell = wShell.lock();
				if (shell)
				{
					sound.setVolume(GAME_SETTINGS.getSoundVolume());
					sound.play();
					shell->setSpeedMultiply(0.5f);
				}
			},
			[wShell = std::weak_ptr<Shell>(shell)]() {
				auto shell = wShell.lock();
				if (shell)
				{
					shell->setSpeedMultiply(1.f);
				}
			},
			GAME_SETTINGS.EFFECT_DURATION
		));

		effects.emplace(EffectType::FastBall, std::make_shared<Effect>(
			sf::Color::Red,
			[wShell = std::weak_ptr<Shell>(shell), &sound = soundEffect]() {
				auto shell = wShell.lock();
				if (shell)
				{
					sound.setVolume(GAME_SETTINGS.getSoundVolume());
					sound.play();
					shell->setSpeedMultiply(1.5f);
				}
			},
			[wShell = std::weak_ptr<Shell>(shell)]() {
				auto shell = wShell.lock();
				if (shell)
				{
					shell->setSpeedMultiply(1.f);
				}
			},
			GAME_SETTINGS.EFFECT_DURATION
		));

		effects.emplace(EffectType::Squidward, std::make_shared<Effect>(
			sf::Color::Yellow,
			[wPlatform = std::weak_ptr<Platform>(player), &sound = soundEffect]() {
				auto platform = wPlatform.lock();
				if (platform)
				{
					sound.setVolume(GAME_SETTINGS.getSoundVolume());
					sound.play();
					platform->setWidth(200.f);
				}
			},
			[wPlatform = std::weak_ptr<Platform>(player)]() {
				auto platform = wPlatform.lock();
				if (platform)
				{
					platform->setWidth(GAME_SETTINGS.PLATFORM_WIDTH_DEFAULT);
				}
			},
			GAME_SETTINGS.EFFECT_DURATION
		));

		std::for_each(effects.begin(), effects.end(), [&](auto& pairEffects) { pairEffects.second->AddObserver(weak_from_this()); });

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
		std::for_each(effects.begin(), effects.end(), [&window](auto& pairEffects) { pairEffects.second->drawOnWindow(window); });

		// Texts
		window.draw(scoreText);
		scoreText.setPosition(0, 0);
		window.draw(triesText);
		triesText.setPosition(GAME_SETTINGS.SCREEN_WIDTH_GAME / 2.f, 0);
		window.draw(pauseNote);
		pauseNote.setPosition(static_cast<float>(GAME_SETTINGS.SCREEN_WIDTH_GAME - 1), 0.f);
	}

	void GameStatePlayingData::update(float deltaTime)
	{
		// Update texts
		scoreText.setString("SCORES: " + std::to_string(score));
		triesText.setString("ATTEMPTS LEFT: " + std::to_string(tries));

		// Update game objects

		std::shared_ptr <Platform> ptrPlayer = std::dynamic_pointer_cast<Platform>(gameObjects[0]);
		std::shared_ptr<Shell> ptrShell = std::dynamic_pointer_cast<Shell>(gameObjects[1]);

		gameObjects[0]->update(mouseMoveX);
		gameObjects[1]->update(deltaTime);

		std::for_each(bricks.begin(), bricks.end(), [deltaTime](auto& brick){ brick->update(deltaTime); });
		std::for_each(effects.begin(), effects.end(), [deltaTime](auto& pairEffects) { pairEffects.second->update(deltaTime); });

		// Effect reflection
		std::for_each(effects.begin(), effects.end(),
			[&](auto& pairEffects)
			{
				pairEffects.second->checkCollision(ptrPlayer);
			});

		if (breackableBricksCount == 0)
		{
			Application::getInstance().getGame().getAudio().playFullSound(AudioManager::ESoundEffect::Victory);
			loadNextLevel();
		} else if (ptrShell->checkState(Shell::EShellState::Striked))
		{
			// Platform reflection
			ptrPlayer->checkCollision(ptrShell);

			// Bricks reflection
			for (auto& brick : bricks)
			{
				if (brick->isAlive() && brick->checkCollision(ptrShell))
				{
					soundHit.setVolume(GAME_SETTINGS.getSoundVolume());
					soundHit.play();
					break;
				}
			}
		} else if (ptrShell->checkState(Shell::EShellState::Fallen))
		{
			--tries;

			if (tries > 0)
			{
				soundFail.setVolume(GAME_SETTINGS.getSoundVolume());
				soundFail.play();

				std::shared_ptr <Platform> ptrPlayer = std::dynamic_pointer_cast<Platform>(gameObjects[0]);
				std::shared_ptr<Shell> ptrShell = std::dynamic_pointer_cast<Shell>(gameObjects[1]);
				ptrShell->attachToPlatform();
			}
			else
			{
				Application::getInstance().getGame().getAudio().playFullSound(AudioManager::ESoundEffect::Death);
				Application::getInstance().getGame().looseGame();
			}
		}
	}

	void GameStatePlayingData::loadNextLevel()
	{
		if (currentLevel > levelManager.getMaxLevel())
		{
			Game& game = Application::getInstance().getGame();
			game.winGame();
		} else
		{
			std::shared_ptr <Platform> ptrPlayer = std::dynamic_pointer_cast<Platform>(gameObjects[0]);
			std::shared_ptr<Shell> ptrShell = std::dynamic_pointer_cast<Shell>(gameObjects[1]);
			ptrShell->attachToPlatform();

			bricks.clear();
			std::for_each(effects.begin(), effects.end(), [](auto& pairEffects) { pairEffects.second->finish(); });

			++currentLevel;
			createLevel();
		}
	}

	void GameStatePlayingData::createLevel()
	{
		for (const auto& pair : brickFactories)
		{
			pair.second->clearCounter();
		}

		float startHeight{ 100.f };
		float startWidth{ 60.f };
		Vector2Df pos = { startWidth, startHeight };
		auto level = levelManager.loadLevel(currentLevel);

		std::for_each(level.begin(), level.end(),
			[&](const BricksRow& row)
			{
				std::for_each(row.begin(), row.end(),
					[&](BrickType brickType)
					{
						bricks.emplace_back(brickFactories.at(brickType)->createBrick(pos));
						bricks.back()->AddObserver(weak_from_this());

						pos.x += GAME_SETTINGS.BRICK_WIDTH_DEFAULT + GAME_SETTINGS.BRICK_SHIFT_WIDTH;
					});
				pos.x = startWidth;
				pos.y += GAME_SETTINGS.BRICK_SHIFT_HEIGHT;
			});

		for (const auto& pair : brickFactories)
		{
			breackableBricksCount += pair.second->getCreatedBreackableBricksCount();
		}
	}

	void GameStatePlayingData::Notify(std::shared_ptr<IObservable> observable)
	{
		if (auto brick = std::dynamic_pointer_cast<Brick>(observable))
		{
			if (!brick->isAlive())
			{
				score += brick->getScore();
				--breackableBricksCount;

				if (std::find_if(effects.begin(), effects.end(), [](auto& pairEffects) { return pairEffects.second->isActivated(); }) == effects.end())
				{
					auto chance = Math::getRandNumTo(100);
					if (GAME_SETTINGS.CHANCE_EFFECT > chance)
					{
						auto condition = [](const std::shared_ptr<Effect>& sEffect)
							{
								return !sEffect->isActivated() && !sEffect->isFalling();
							};

						std::vector<EffectType> filtered;
						for (const auto& effect : effects)
						{
							if (condition(effect.second))
							{
								filtered.push_back(effect.first);
							}
						}

						if (!filtered.empty())
						{
							effects.at(filtered[Math::getRandNumTo((int)filtered.size())])->create(brick->getPosition());
						}
					}
				}
			}
		} else if (auto effect = std::dynamic_pointer_cast<Effect>(observable))
		{
			effect->activate();
		}
	}
}