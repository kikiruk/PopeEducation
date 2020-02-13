#include <algorithm>
#include <cmath>
#include "Motorcycle.h"

namespace assignment2
{
	Motorcycle::Motorcycle() :
		Vehicle(2)
	{
	}

	const Motorcycle& Motorcycle::operator=(const Motorcycle& other)
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

	unsigned int Motorcycle::GetMaxSpeed() const
	{
		return static_cast<unsigned int>(std::max((-pow((static_cast<double>(mPassengerWeight) / 15), 3) + (2 * static_cast<double>(mPassengerWeight)) + 400), static_cast <double>(0)) + 0.5);
	}

	unsigned int Motorcycle::GetDriveSpeed() const
	{
		return static_cast<unsigned int>(std::max((-pow((static_cast<double>(mPassengerWeight) / 15), 3) + (2 * static_cast<double>(mPassengerWeight)) + 400), static_cast <double>(0)) + 0.5);
	}

	void Motorcycle::Travel()
	{
		if (mTravelCount != 5)
			mDistance += GetMaxSpeed();

		mTravelCount = (mTravelCount + 1) % 6;
	}
}