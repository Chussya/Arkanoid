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
			player.move(static_cast<float>(event.mouseMove.x));
		}
	}

	void GameStatePlayingData::InitGameState(Game& game)
	{
		// Init fonts
		assert(font.loadFromFile(RESOURCES_PATH + "Fonts/arial.ttf"));

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

		/// Set platform

		player.setStartPosition();

		/// Set shell:

		shell.setSpeed(game.getGameSettigns().shellSpeed);

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
		pauseNote.setPosition(SCREEN_WIDTH_GAME - 1, 0);
	}

	void GameStatePlayingData::UpdateGameState(Game& game, float deltaTime)
	{
		// Update scores:
		//data.scoreText.setString("SCORES: " + std::to_string(data.numEatenApples));\
		
		shell.reflection(player.getSize());
		shell.move(deltaTime);
	}

	void GameStatePlayingData::ShutdownGameState(Game& game)
	{
		// Stop music
		//game.music.stop();
	}
}