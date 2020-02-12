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
		return static_cast<unsigned int>(std::max((-pow((static_cast<double>(mPassengerWeight) / 15), 3)
			+ (2 * static_cast<double>(mPassengerWeight)) + 400), static_cast <double>(0)) + 0.5);
	}

	unsigned int Motorcycle::GetDriveSpeed() const
	{
		return static_cast<unsigned int>(std::max((-pow((static_cast<double>(mPassengerWeight)/ 15), 3)
			+ (2 * static_cast<double>(mPassengerWeight)) + 400), static_cast <double>(0)) + 0.5);
	}

	void Motorcycle::Travel()
	{
		if (mTravelCount != 5)
			mDistance += GetMaxSpeed();

		mTravelCount = (mTravelCount + 1) % 6;
	}
}