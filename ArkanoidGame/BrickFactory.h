#pragma once

#include <memory>
#include "SFML/Graphics.hpp"

#include "Vector2D.h"

namespace ArkanoidGame
{
	class Brick;

	class BrickFactory
	{
	protected:
		int createdBreackableBricksCount = 0;
	public:
		virtual ~BrickFactory() = default;

		virtual std::shared_ptr<Brick> createBrick(const Vector2Df& position) = 0;

		void clearCounter();
		int getCreatedBreackableBricksCount();
	};

	class SimpleBrickFactory final : public BrickFactory
	{
	public:
		~SimpleBrickFactory() override = default;

		std::shared_ptr<Brick> createBrick(const Vector2Df& position) override;
	};

	class DurableBrickFactory final : public BrickFactory
	{
	public:
		~DurableBrickFactory() override = default;

		std::shared_ptr<Brick> createBrick(const Vector2Df& position) override;
	};

	class UnbreackableBrickFactory final : public BrickFactory
	{
	public:
		~UnbreackableBrickFactory() override = default;

		std::shared_ptr<Brick> createBrick(const Vector2Df& position) override;
	};
}