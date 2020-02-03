#define PI 3.14

#include "CircleLawn.h"

namespace lab5
{
	CircleLawn::CircleLawn(unsigned int radius) :
		mRadius(radius)
	{
	}

	unsigned int CircleLawn::GetArea() const
	{
		double area = static_cast<double>(mRadius) * mRadius * PI;

		return area + 0.5;
	}
}