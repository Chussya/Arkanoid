#include "BrickFactory.h"

#include "Brick.h"

namespace ArkanoidGame
{
	void BrickFactory::clearCounter()
	{
		createdBreackableBricksCount = 0;
	}

	int BrickFactory::getCreatedBreackableBricksCount()
	{
		return createdBreackableBricksCount;
	}

	std::shared_ptr<Brick> SimpleBrickFactory::createBrick(const Vector2Df& position)
	{
		++createdBreackableBricksCount;
		return std::make_shared<SmoothDestroybleBrick>(position);
	}

	std::shared_ptr<Brick> UnbreackableBrickFactory::createBrick(const Vector2Df& position)
	{
		return std::make_shared<UnbreackableBrick>(position);
	}

	std::shared_ptr<Brick> DurableBrickFactory::createBrick(const Vector2Df& position)
	{
		++createdBreackableBricksCount;
		return std::make_shared<DurableBrick>(position);
	}
}
