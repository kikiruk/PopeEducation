#include <cmath>
#include <algorithm>
#include "UBoat.h"

namespace assignment2
{
	UBoat::UBoat() :
		Vehicle(50)
	{
	}

	const UBoat& UBoat::operator=(const UBoat& other)
	{
		if (this != &other)
		{
			for (unsigned int i = 0; i < mCount; i++)
				delete mPassengers[i];

			mCount = other.mCount;
			mDistance = 0;
			mTravelCount = 0;
			mPassengerWeight = other.mPassengerWeight;

			for (unsigned int i = 0; i < mCount; i++)
				mPassengers[i] = new Person(*(other.mPassengers[i]));
		}

		return *this;
	}

	unsigned int UBoat::GetSailSpeed() const
	{
		return static_cast<unsigned int>(std::max((550 - static_cast<double>(mPassengerWeight) / 10), static_cast<double>(200)) + 0.5);
	}

	unsigned int UBoat::GetDiveSpeed() const
	{
		return static_cast<unsigned int>(500 * log((static_cast<double>(mPassengerWeight) + 150) / 150) + 30 + 0.5);
	}

	unsigned int UBoat::GetMaxSpeed() const
	{
		return std::max(GetSailSpeed(), GetDiveSpeed());
	}

	void UBoat::Travel()
	{
		if (mTravelCount == 0 || mTravelCount == 1)
			mDistance += GetMaxSpeed();

		mTravelCount = (mTravelCount + 1) % 6;
	}
}