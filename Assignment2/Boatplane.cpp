#define M_E        2.71828182845904523536   // e

#include <algorithm>
#include <cmath>
#include "Boatplane.h"

namespace assignment2
{
	Boatplane::Boatplane(unsigned int maxPassengersCount) :
		Vehicle(maxPassengersCount)
	{
	}

	unsigned int Boatplane::GetMaxSpeed() const
	{
		return std::max(GetFlySpeed(), GetSailSpeed());
	}
	unsigned int Boatplane::GetFlySpeed() const
	{
		return static_cast<unsigned int>(150 * pow(M_E, ((static_cast<double>(500) - mPassengerWeight) / 300)) + 0.5);
	}
	unsigned int Boatplane::GetSailSpeed() const
	{
		return static_cast<unsigned int>(std::max((static_cast<double>(800) - 1.7 * mPassengerWeight), static_cast<double>(20)) + 0.5);
	}

	void Boatplane::Travel()
	{
		if (mTravelCount == 0)
			mDistance += GetMaxSpeed();

		mTravelCount = (mTravelCount + 1) % 4;
	}
}