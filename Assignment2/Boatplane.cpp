#define _USE_MATH_DEFINES

#include <algorithm>
#include <cmath>
#include "Boatplane.h"

namespace assignment2
{
	Boatplane::Boatplane(unsigned int maxPassengersCount)
		:Vehicle(maxPassengersCount)
	{
	}

	Boatplane::~Boatplane()
	{
	}

	unsigned int Boatplane::GetMaxSpeed() const
	{
		return std::max(GetFlySpeed(), GetSailSpeed());
	}
	unsigned int Boatplane::GetFlySpeed() const
	{
		return 150 * pow(M_E , ((double)(500 - mPassengerWeight) / 300)) + 0.5;
	}
	unsigned int Boatplane::GetSailSpeed() const
	{
		return std::max((800 - (double)1.7 * mPassengerWeight), (double)20) + 0.5;
	}

	void Boatplane::Travel()
	{
		if (mTravelCount == 0)
			mDistance += GetMaxSpeed();

		mTravelCount = (mTravelCount + 1) % 4;
	}
}