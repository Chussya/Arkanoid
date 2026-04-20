#include "Math.h"

#include <algorithm>

namespace ArkanoidGame
{
	bool Math::isCircleCollideRect(Vector2Df circlePos, float circleRad, Vector2Df rectPos, float rectWidth, float rectHeight)
	{
        // Find the closest point on the rectangle to the circle center
        float closestX = std::max(rectPos.x - rectWidth / 2, std::min(circlePos.x, rectPos.x + rectWidth / 2));
        float closestY = std::max(rectPos.y - rectHeight / 2, std::min(circlePos.y, rectPos.y + rectHeight / 2));

        // Calculate the distance between the circle's center and this closest point
        float distanceX = circlePos.x - closestX;
        float distanceY = circlePos.y - closestY;

        // Use distance squared for performance (avoids sqrt)
        float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

        return distanceSquared < circleRad * circleRad;
	}
}