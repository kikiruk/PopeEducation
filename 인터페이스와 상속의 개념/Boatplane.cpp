#define M_E        2.71828182845904523536   // e

#include <algorithm>
#include <cmath>
#include "Boatplane.h"
#include "Airplane.h"
#include "Boat.h"

namespace assignment2
{
	Boatplane::Boatplane(unsigned int maxPassengersCount) :
		Vehicle(maxPassengersCount)
	{
	}

	Boatplane::Boatplane(Airplane* airplane, Boat* boat) :
		Vehicle(airplane->mMaxPassengerCount + boat->mMaxPassengerCount)
	{
		for (unsigned int i = 0; i < airplane->mCount; i++)
		{
			this->mPassengers[this->mCount++] = airplane->mPassengers[i];
			airplane->mPassengers[i] = nullptr;
		}

		for (unsigned int i = 0; i < boat->mCount; i++)
		{
			this->mPassengers[this->mCount++] = boat->mPassengers[i];
			boat->mPassengers[i] = nullptr;
		}

		airplane->mCount = 0;
		boat->mCount = 0;
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