#define PI 3.14

#include "CircleLawn.h"

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

		return static_cast<unsigned int>(area + 0.5);
	}
}