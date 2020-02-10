#include <cstring>
#include "Vehicle.h"

namespace assignment2
{
	Vehicle::Vehicle(unsigned int maxPassengersCount) :
		mMaxPassengerCount(maxPassengersCount),
		mCount(0),
		mDistance(0), 
		mTravelCount(0)
	{
		mPassengers = new Person*[mMaxPassengerCount];
	}

	Vehicle::Vehicle(const Vehicle & other) :
		mMaxPassengerCount(other.mMaxPassengerCount),
		mCount(other.mCount)
	{
		mPassengers = new Person*[mMaxPassengerCount];

		for (int i = 0; i < mCount; i++)
			mPassengers[i] = new Person(*(other.mPassengers[i]));
	}

	Vehicle::~Vehicle()
	{
		for (int i = 0; i < mCount; i++)
			delete mPassengers[i];

		delete[] mPassengers;
	}

	bool Vehicle::AddPassenger(const Person* person)
	{
		if (mCount == mMaxPassengerCount)
			return false;

		mPassengers[mCount++] = person;

		return true;
	}

	bool Vehicle::RemovePassenger(unsigned int i)
	{
		if (mCount <= i)
			return false;

		delete mPassengers[i];

		if (mCount - 1 != i)
			memcpy(mPassengers + i, mPassengers + i + 1, mCount - 1 - i);

		mCount--;

		return false;
	}

	unsigned int Vehicle::GetPassengersCount() const
	{
		return mCount;
	}

	unsigned int Vehicle::GetMaxPassengersCount() const
	{
		return mMaxPassengerCount;
	}

	const Person* Vehicle::GetPassenger(unsigned int i) const
	{
		if (i >= mCount)
			return NULL;

		return mPassengers[i];
	}
}