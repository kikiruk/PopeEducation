#include "EquilateralTriangleLawn.h"

namespace lab5
{
	EquilateralTriangleLawn::EquilateralTriangleLawn(unsigned int oneSide) :
		mOneSide(oneSide)
	{
	}

	unsigned int EquilateralTriangleLawn::GetArea() const
	{
		double area = static_cast<double>(mOneSide) * mOneSide * 0.4330127018922193;

		return area + 0.5;
	}

	unsigned int EquilateralTriangleLawn::GetMinimumFencesCount() const
	{
		return mOneSide * 12;
	}

	unsigned int EquilateralTriangleLawn::GetFencePrice(eFenceType fenceType) const
	{
		double price = 0;

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

		return mOneSide * 3 * price;
	}
}