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
		return Boatplane(&plane, this);
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