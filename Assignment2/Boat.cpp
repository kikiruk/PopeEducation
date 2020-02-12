#include <algorithm>
#include "Boat.h"
#include "Airplane.h"

namespace assignment2
{
	Boat::Boat(unsigned int maxPassengersCount) :
		Vehicle(maxPassengersCount)
	{
	}

	Boatplane Boat::operator+(Airplane& plane)
	{
		Boatplane bp(this->mMaxPassengerCount + plane.mMaxPassengerCount);

		for (unsigned int i = 0; i < plane.mCount; i++)
		{
			bp.mPassengers[bp.mCount++] = plane.mPassengers[i];
			plane.mPassengers[i] = nullptr;
		}

		for (unsigned int i = 0; i < this->mCount; i++)
		{
			bp.mPassengers[bp.mCount++] = this->mPassengers[i];
			mPassengers[i] = nullptr;
		}

		this->mCount = 0;
		plane.mCount = 0;

		return bp;
	}

	unsigned int Boat::GetMaxSpeed() const
	{
		return static_cast<unsigned int>(std::max((800 - 10 * static_cast<int>(mPassengerWeight)), 20));
	}

	unsigned int Boat::GetSailSpeed() const
	{
		return static_cast<unsigned int>(std::max((800 - 10 * static_cast<int>(mPassengerWeight)), 20));
	}

	void Boat::Travel()
	{
		if (mTravelCount == 0 || mTravelCount == 1)
			mDistance += GetMaxSpeed();

		mTravelCount = (mTravelCount + 1) % 3;
	}
}