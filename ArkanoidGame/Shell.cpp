#include "Shell.h"

#include <cassert>

#include "GameSettings.h"

namespace ArkanoidGame
{
	/// Public

	Shell::Shell() :
		state{ EShellState::Empty },
		platformData{ nullptr, nullptr },
		speedMultiply{ 1.f },
		Collidable(Collidable::ECollisionShape::Circle),
		GameObject(GAME_SETTINGS.RESOURCES_PATH + GAME_SETTINGS.IMG_PATH + "shell.png", { 0.f, 0.f }, GAME_SETTINGS.BALL_RADIUS_DEFAULT * 2, GAME_SETTINGS.BALL_RADIUS_DEFAULT * 2)
	{
		setSpriteOrigin(0.5f, 0.5f);
	}

	Shell::~Shell() {}

	void Shell::setSpeedMultiply(const float speed)
	{
		this->speedMultiply = speed;
	}

	void Shell::setPlatformData(const PlatformData platformData)
	{
		this->platformData = platformData;
	}

	bool Shell::checkState(const EShellState state)
	{
		return this->state.IsBitMaskOn(state);
	}

	void Shell::invertX()
	{
		vectorSpeed.x *= -1;
	}

	void Shell::invertY()
	{
		vectorSpeed.y *= -1;
	}

	void Shell::strike()
	{
		state.SetMask(EShellState::Striked);
		vectorSpeed.y = -GAME_SETTINGS.getShellSpeed();

		if (getPosition().x - (getRect().width / 2) <= 0)
		{
			sprite.setPosition({ getPosition().x + (getRect().width / 2) + 1.f, getPosition().y });
		} else if (getPosition().x + (getRect().width / 2) >= GAME_SETTINGS.SCREEN_WIDTH_GAME)
		{
			sprite.setPosition({ getPosition().x - (getRect().width / 2) - 1.f, getPosition().y });
		}
	}

	void Shell::collidePlatform(ECollisionSide collision)
	{
		vectorSpeed.x = vectorSpeed.y * ((sprite.getPosition().x - platformData.ptrPos->x) / (*platformData.ptrWidth / 2));

		setCollisionSide(collision);
	}

	void Shell::attachToPlatform()
	{
		sprite.setPosition({ platformData.ptrPos->x, platformData.ptrPos->y - GAME_SETTINGS.PLATFORM_HEIGHT_DEFAULT });
		state.SetMask(EShellState::Empty);

		vectorSpeed.x = 0;
		vectorSpeed.y = 0;
	}

	void Shell::addState(const EShellState& state)
	{
		this->state.AddMask(state);
	}

	void Shell::update(const float deltaTime)
	{
		if (state.IsBitMaskOn(EShellState::Striked))
		{
			sprite.setPosition(sprite.getPosition().x + vectorSpeed.x * speedMultiply * deltaTime, sprite.getPosition().y + vectorSpeed.y * speedMultiply * deltaTime);

			if (getRect().top <= 0.f)
			{
				invertY();
			} else if (getRect().left <= 0.f || getRect().left + getRect().width >= GAME_SETTINGS.SCREEN_WIDTH_GAME)
			{
				invertX();
			} else if (getRect().top + getRect().height >= GAME_SETTINGS.SCREEN_HEIGHT_GAME)
			{
				state.SetMask(EShellState::Fallen);
			}
		} else
		{
			sprite.setPosition({ platformData.ptrPos->x, sprite.getPosition().y });
		}
	}

	void Shell::onHit()
	{
		if (state.IsBitMaskOn(EShellState::Striked))
		{
			if (getCollisionSide() == ECollisionSide::Right || getCollisionSide() == ECollisionSide::Left)
			{
				invertX();
			} else if (getCollisionSide() == ECollisionSide::Top || getCollisionSide() == ECollisionSide::Bottom)
			{
				invertY();
			}  else if (getCollisionSide() == ECollisionSide::Angle)
			{
				invertX();
				invertY();
			}
			setCollisionSide(ECollisionSide::Empty);
			Emit();
		} else if (state.IsBitMaskOn(EShellState::Fallen))
		{

		}
	}

	bool Shell::isCollide(std::shared_ptr<Collidable> collidable)
	{
		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidable);
		assert(gameObject);
		return getRect().intersects(gameObject->getRect());
	}
}