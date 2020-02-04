#include <cmath>
#include "CircleLawn.h"

#define PI 3.14

namespace lab5
{
	CircleLawn::CircleLawn(unsigned int radius) :
		Lawn(),
		mRadius(radius)
	{
	}

	unsigned int CircleLawn::GetArea() const
	{
		double area = static_cast<double>(mRadius) * mRadius * PI;

		return static_cast<unsigned int>(ceil(area));
	}
}