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
		Boatplane bp(this->mCount + boat.mCount);

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
		return 0;
	}

	unsigned int Airplane::GetFlySpeed() const
	{
		return 200 * pow(e, ((-(mCount * ) + 800) / 500));
	}

	unsigned int Airplane::GetDriveSpeed() const
	{
		return 0;
	}

	void Airplane::Travel()
	{
		if(mTravelCount == 0)
			//±¸Çö

		mTravelCount = (mTravelCount + 1) % 3;
	}
}