#include <algorithm>
#include <cmath>
#include "Motorcycle.h"

namespace assignment2
{
	Motorcycle::Motorcycle() :
		Vehicle(2)
	{
	}

	Motorcycle::~Motorcycle()
	{
	}

	unsigned int Motorcycle::GetMaxSpeed() const
	{
		return std::max((-pow(((double)mPassengerWeight / 15), 3) + (2 * (double)mPassengerWeight) + 400), (double)0) + 0.5;
	}

	unsigned int Motorcycle::GetDriveSpeed() const
	{
		return std::max((-pow(((double)mPassengerWeight / 15) , 3) + (2 * (double)mPassengerWeight) + 400), (double)0) + 0.5;
	}

	void Motorcycle::Travel()
	{
		if (mTravelCount != 5)
			mDistance += GetMaxSpeed();

		mTravelCount = (mTravelCount + 1) % 6;
	}
}