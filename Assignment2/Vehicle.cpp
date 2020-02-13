#include <cstring>
#include "Vehicle.h"

namespace assignment2
{
	Vehicle::Vehicle(unsigned int maxPassengersCount) :
		mMaxPassengerCount(maxPassengersCount),
		mCount(0),
		mDistance(0),
		mTravelCount(0),
		mPassengerWeight(0),
		mTrailer(nullptr)
	{
		mPassengers = new const Person* [mMaxPassengerCount];
	}

	Vehicle::Vehicle(const Vehicle& other) :
		mMaxPassengerCount(other.mMaxPassengerCount),
		mCount(other.mCount),
		mDistance(other.mDistance),
		mTravelCount(other.mTravelCount),
		mPassengerWeight(other.mPassengerWeight),
		mTrailer(nullptr)
	{
		mPassengers = new const Person* [other.mMaxPassengerCount];

		for (unsigned int i = 0; i < other.mCount; i++)
			mPassengers[i] = new Person(*(other.mPassengers[i]));

		if (other.mTrailer != nullptr)
			mTrailer = new Trailer(*other.mTrailer);
	}

	Vehicle::~Vehicle()
	{
		if (mTrailer != nullptr)
			delete mTrailer;

		for (unsigned int i = 0; i < mCount; i++)
			delete mPassengers[i];

		delete[] mPassengers;
	}

	const Vehicle& Vehicle::operator=(const Vehicle& other)
	{
		if (this != &other)
		{
			for (unsigned int i = 0; i < mCount; i++)
				delete mPassengers[i];

			delete[] mPassengers;

			if (mTrailer != nullptr)
				delete mTrailer;

			mMaxPassengerCount = other.mMaxPassengerCount;
			mCount = other.mCount;
			mDistance = other.mDistance;
			mTravelCount = other.mTravelCount;
			mPassengerWeight = other.mPassengerWeight;
			mTrailer = nullptr;

			mPassengers = new const Person* [other.mMaxPassengerCount];

			for (unsigned int i = 0; i < mCount; i++)
				mPassengers[i] = new Person(*(other.mPassengers[i]));

			if (other.mTrailer != nullptr)
				mTrailer = new Trailer(*other.mTrailer);
		}

		return *this;
	}

	bool Vehicle::AddPassenger(const Person* person)
	{
		if (mCount == mMaxPassengerCount)
			return false;

		if (person == NULL)
			return false;

		for (unsigned int i = 0; i < mCount; i++)
		{
			if (mPassengers[i] == person)
				return false;
		}

		mPassengers[mCount++] = person;

		mPassengerWeight += person->GetWeight();

		return true;
	}

	bool Vehicle::RemovePassenger(unsigned int i)
	{
		if (mCount <= i)
			return false;

		mPassengerWeight -= mPassengers[i]->GetWeight();

		delete mPassengers[i];

		if (mCount - 1 != i)
			memcpy(mPassengers + i, mPassengers + i + 1, sizeof(Person*) * (mCount - 1 - i));

		mCount--;

		return true;
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