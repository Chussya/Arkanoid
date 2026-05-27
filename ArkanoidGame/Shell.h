#pragma once

#include <memory>

#include "Math.h"
#include "GameObject.h"
#include "Collidable.h"
#include "IObservable.h"

namespace ArkanoidGame
{
	class GameSettings;

	struct PlatformData
	{
		// Special pointer of platform's width
		float* ptrWidth;
		// Special pointer of platform's position
		Vector2Df* ptrPos;
	};

	class Shell : public GameObject, public Collidable, public IObservable
	{
	public:
		enum class EShellState
		{
			Striked = 1 << 0,
			Fallen = 1 << 1,

			Empty = 0
		};

	private:
		// State of shell
		Math::BitMask<EShellState> state;

		// Speed of general vector of move
		float speedMultiply;

		// Speed of vectors X and Y
		Vector2Df vectorSpeed;

		PlatformData platformData;

	public:
		Shell();
		~Shell();

		/// Setters

		void setSpeedMultiply(const float speed);
		void setPlatformData(const PlatformData platformData);

		/// Interaction

		bool checkState(const EShellState state);

		void invertX();
		void invertY();

		void strike();
		void attachToPlatform();

		void collidePlatform(ECollisionSide collision);
		void addState(const EShellState& state);

		/// Inherited via GameObject

		void update(const float deltaTime) override;

		/// Inherited via Collidable

		void onHit() override;
		bool isCollide(std::shared_ptr<Collidable> collidable) override;
	};
}