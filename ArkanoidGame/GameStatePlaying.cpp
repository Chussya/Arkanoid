#include "GameStatePlaying.h"

#include <cassert>
#include <functional>

#include "Game.h"
#include "MenuItem.h"

namespace ArkanoidGame
{
	GameStatePlayingData::GameStatePlayingData() {}

	void GameStatePlayingData::HandleGameStateWindowEvent(Game& game, const sf::Event event)
	{
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			player.strikeShell(shell);
		}
		if (event.type == sf::Event::MouseMoved)
		{
			mouseMoveX = static_cast<float>(event.mouseMove.x);
		}
	}

	void GameStatePlayingData::InitGameState(Game& game)
	{
		// Init fonts
		assert(font.loadFromFile(game.getGameSettigns().RESOURCES_PATH + "Fonts/arial.ttf"));

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

		/// Init platform

		player.init(game.getGameSettigns());
		player.setStartPosition(static_cast<float>(game.getGameSettigns().SCREEN_WIDTH_GAME), static_cast<float>(game.getGameSettigns().SCREEN_HEIGHT_GAME));

		/// Set shell:

		shell.init(game.getGameSettigns());
		shell.setSpeed(game.getGameSettigns().getShellSpeed());

		player.attachShell(shell);

		//game.ptrPlayerScores = &data.numEatenApples;
	}

	void GameStatePlayingData::DrawGameState(Game& game, sf::RenderWindow& window)
	{
		// Game objects

		player.drawOnWindow(window);
		shell.drawOnWindow(window);

		// Texts
		window.draw(scoreText);
		scoreText.setPosition(0, 0);
		window.draw(pauseNote);
		pauseNote.setPosition(static_cast<float>(game.getGameSettigns().SCREEN_WIDTH_GAME - 1), 0.f);
	}

	void GameStatePlayingData::UpdateGameState(Game& game, float deltaTime)
	{
		// Update scores:
		//data.scoreText.setString("SCORES: " + std::to_string(data.numEatenApples));\

		// Check shell reflection
		shell.reflection(static_cast<float>(game.getGameSettigns().SCREEN_WIDTH_GAME), static_cast<float>(game.getGameSettigns().SCREEN_HEIGHT_GAME), player.getSize());

		// Move game objects
		shell.move(deltaTime);
		player.move(mouseMoveX);
	}

	void GameStatePlayingData::ShutdownGameState(Game& game)
	{
		// Stop music
		//game.music.stop();
	}
}