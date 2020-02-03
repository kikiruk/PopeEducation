#include "SquareLawn.h"

namespace lab5
{
	SquareLawn::SquareLawn(unsigned int width) :
		Lawn(),
		mWidth(width)
	{
	}

	unsigned int SquareLawn::GetArea() const
	{
		return mWidth * mWidth;
	}

	unsigned int SquareLawn::GetMinimumFencesCount() const
	{
		return mWidth * 16;
	}

	unsigned int SquareLawn::GetFencePrice(eFenceType fenceType) const
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

		return mWidth * 4 * price;
	}
}