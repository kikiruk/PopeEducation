#define M_E        2.71828182845904523536   // e

#include <cmath>
#include <algorithm>
#include "Airplane.h"
#include "Boat.h"

namespace assignment2
{
	Airplane::Airplane(unsigned int maxPassengersCount) :
		Vehicle(maxPassengersCount)
	{
	}

	Boatplane Airplane::operator+(Boat& boat)
	{
		const Person** passengersTmp = new const Person*[this->mMaxPassengerCount + boat.mMaxPassengerCount];
		unsigned int index = 0;

		for (unsigned int i = 0; i < this->mCount; i++)
		{
			passengersTmp[index++] = this->mPassengers[i];
			this->mPassengers[i] = nullptr;
		}

		for (unsigned int i = 0; i < boat.mCount; i++)
		{
			passengersTmp[index++] = boat.mPassengers[i];
			boat.mPassengers[i] = nullptr;
		}

		this->mCount = 0;
		boat.mCount = 0;

		return Boatplane(this->mMaxPassengerCount + boat.mMaxPassengerCount, index, passengersTmp);
	}

	unsigned int Airplane::GetMaxSpeed() const
	{
		return std::max(GetFlySpeed(), GetDriveSpeed());
	}

	unsigned int Airplane::GetFlySpeed() const
	{
		return static_cast<unsigned int>(200 * pow(M_E, ((static_cast<double>(800) - mPassengerWeight) / 500)) + 0.5);
	}

	unsigned int Airplane::GetDriveSpeed() const
	{
		return static_cast<unsigned int>(4 * pow(M_E, ((static_cast <double>(400) - mPassengerWeight) / 70)) + 0.5);
	}

	void Airplane::Travel()
	{
		if (mTravelCount == 0)
			mDistance += GetMaxSpeed();

		mTravelCount = (mTravelCount + 1) % 4;
	}
}