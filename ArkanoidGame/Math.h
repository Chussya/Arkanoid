#pragma once
#include "Vector2D.h"

namespace ArkanoidGame
{
	class Math
	{
	public:

		template <class Enum>
		class BitMask
		{
		private:
			int mask;

		public:
			BitMask(Enum defaultMask)
			{
				mask = static_cast<int>(defaultMask);
			}

			void TurnOnMask(Enum flag)
			{
				mask |= static_cast<int>(flag);
			}

			void TurnOffMask(Enum flag)
			{
				mask &= ~static_cast<int>(flag);
			}

			void UpdateBitMask(Enum newMask)
			{
				int newMaskInt = static_cast<int>(newMask);
				mask & newMaskInt ?
					mask &= ~newMaskInt :
					mask |= newMaskInt;
			}

			bool IsBitMaskOn(Enum checkMask)
			{
				return mask & static_cast<int>(checkMask);
			}
		};

		static bool isCircleCollideRect(Vector2Df circlePos, float circleRad, Vector2Df rectPos, float rectWidth, float rectHeight);
	};
}