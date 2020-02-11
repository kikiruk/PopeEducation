#include <algorithm>
#include "Boat.h"
#include "Airplane.h"

namespace assignment2
{
	Boat::Boat(unsigned int maxPassengersCount)
		:Vehicle(maxPassengersCount)
	{
	}

	Boat::~Boat()
	{
	}

	Boatplane Boat::operator+(Airplane& plane)
	{
		Boatplane bp(this->mMaxPassengerCount + plane.mMaxPassengerCount);

		for (int i = 0; i < this->mCount; i++)
		{
			bp.mPassengers[bp.mCount++] = new Person(*this->mPassengers[i]);
			delete this->mPassengers[i];
		}

		for (int i = 0; i < plane.mCount; i++)
		{
			bp.mPassengers[bp.mCount++] = new Person(*(plane.mPassengers[i]));
			delete plane.mPassengers[i];
		}

		this->mCount = 0;
		plane.mCount = 0;

		return bp;
	}

	unsigned int Boat::GetMaxSpeed() const
	{
		return std::max((800 - 10 * mPassengerWeight), (unsigned int)20) + 0.5;
	}

	unsigned int Boat::GetSailSpeed() const
	{
		return std::max((800 - 10 * mPassengerWeight), (unsigned int)20) + 0.5;
	}

	void Boat::Travel()
	{
		if (mTravelCount == 0 || mTravelCount == 1)
			mDistance += GetMaxSpeed();

		mTravelCount = (mTravelCount + 1) % 3;
	}
}