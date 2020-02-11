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

	Airplane::~Airplane()
	{
	}

	Boatplane Airplane::operator+(Boat& boat)
	{
		Boatplane bp(this->mMaxPassengerCount + boat.mMaxPassengerCount);

		for (int i = 0; i < this->mCount; i++)
		{
			bp.mPassengers[bp.mCount++] = new Person(*this->mPassengers[i]);
			delete this->mPassengers[i];
		}

		for (int i = 0; i < boat.mCount; i++)
		{
			bp.mPassengers[bp.mCount++] = new Person(*(boat.mPassengers[i]));
			delete boat.mPassengers[i];
		}

		this->mCount = 0;
		boat.mCount = 0;

		return bp;
	}

	unsigned int Airplane::GetMaxSpeed() const
	{
		return std::max(GetFlySpeed(), GetDriveSpeed());
	}

	unsigned int Airplane::GetFlySpeed() const
	{
		return (double)200 * pow(M_E, ((double)(800 - mPassengerWeight) / 500)) + 0.5;
	}

	unsigned int Airplane::GetDriveSpeed() const
	{
		return (double)4 * pow(M_E, ((double)(400 - mPassengerWeight) / 70)) + 0.5;
	}

	void Airplane::Travel()
	{
		if (mTravelCount == 0)
			mDistance += GetMaxSpeed();

			mTravelCount = (mTravelCount + 1) % 4;
	}
}