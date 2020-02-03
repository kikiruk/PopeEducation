#include "RectangleLawn.h"

namespace lab5
{
	RectangleLawn::RectangleLawn(unsigned int width, unsigned int height) :
		mWidth(width),
		mHeight(height)
	{
	}

	unsigned int RectangleLawn::GetArea() const
	{
		return mWidth * mHeight;
	}

	unsigned int RectangleLawn::GetMinimumFencesCount() const
	{
		return ((mWidth * 2) + (mHeight * 2)) * 4;
	}

	unsigned int RectangleLawn::GetFencePrice(eFenceType fenceType) const
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

		return ((mWidth * 2) + (mHeight * 2)) * price;
	}
}