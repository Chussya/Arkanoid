#pragma once

#include <random>

#include "Vector2D.h"

namespace ArkanoidGame
{
	class Math
	{
	public:
		const float PI{ 3.14159f };

		template <class Enum>
		class BitMask
		{
		private:
			int mask;

		public:
			BitMask(Enum mask) : mask { static_cast<int>(mask) } {}

			// Turn on mask without other changes
			void AddMask(Enum flag)
			{
				mask |= static_cast<int>(flag);
			}

			// Turn off mask without other changes
			void DeleteMask(Enum flag)
			{
				mask &= ~static_cast<int>(flag);
			}

			void SetMask(Enum mask)
			{
				this->mask = static_cast<int>(mask);
			}

			bool IsBitMaskOn(Enum checkMask)
			{
				return mask & static_cast<int>(checkMask);
			}
		};

		static int getRandNumTo(int num)
		{
			return std::rand() % num;
		}
	};
}