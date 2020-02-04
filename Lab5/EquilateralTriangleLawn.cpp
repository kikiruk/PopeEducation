#include <cmath>
#include "EquilateralTriangleLawn.h"

namespace lab5
{
	EquilateralTriangleLawn::EquilateralTriangleLawn(unsigned int oneSide) :
		Lawn(),
		mOneSide(oneSide)
	{
	}

	unsigned int EquilateralTriangleLawn::GetArea() const
	{
		double area = static_cast<double>(mOneSide) * mOneSide * sqrt(3) / 4;

		return static_cast<unsigned int>(area + 0.5);
	}

	unsigned int EquilateralTriangleLawn::GetMinimumFencesCount() const
	{
		return mOneSide * 12;
	}

	unsigned int EquilateralTriangleLawn::GetFencePrice(eFenceType fenceType) const
	{
		unsigned int price = 0;

		switch (fenceType)
		{
		case RED_CEDAR:
			price = 6;
			break;

		case SPRUCE:
			price = 7;
			break;

		default:
			break;
		}

		return mOneSide * 12 * price;
	}
}