#include <cmath>
#include <algorithm>
#include "UBoat.h"

namespace assignment2
{
	UBoat::UBoat() :
		Vehicle(50)
	{
	}

	UBoat::~UBoat()
	{
	}

	unsigned int UBoat::GetSailSpeed() const
	{
		return std::max((550 - (double)mPassengerWeight / 10), (double)200) + 0.5;
	}

	unsigned int UBoat::GetDiveSpeed() const
	{
		return 500 * log(((double)mPassengerWeight + 150) / 150) + 30 + 0.5;
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