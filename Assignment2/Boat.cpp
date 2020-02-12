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
		const Person** passengersTmp = new const Person * [this->mMaxPassengerCount + plane.mMaxPassengerCount];
		unsigned int index = 0;

		for (unsigned int i = 0; i < plane.mCount; i++)
		{
			passengersTmp[index++] = plane.mPassengers[i];
			plane.mPassengers[i] = nullptr;
		}

		for (unsigned int i = 0; i < this->mCount; i++)
		{
			passengersTmp[index++] = this->mPassengers[i];
			mPassengers[i] = nullptr;
		}

		this->mCount = 0;
		plane.mCount = 0;

		return Boatplane(this->mMaxPassengerCount + plane.mMaxPassengerCount, index, passengersTmp);
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