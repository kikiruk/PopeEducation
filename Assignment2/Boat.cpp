#include "Boat.h"
#include "Airplane.h"

namespace assignment2
{
	Boat::Boat(unsigned int maxPassengersCount)
		:Vehicle(maxPassengersCount)
	{
	}

	Boat::~Boat()
	{
	}

	Boatplane Boat::operator+(Airplane& plane)
	{
		Boatplane bp(this->mCount + plane.mCount);

		for (int i = 0; i < this->mCount; i++)
		{
			bp.mPassengers[bp.mCount++] = new Person(*this->mPassengers[i]);
			delete this->mPassengers[i];
		}

		for (int i = 0; i < plane.mCount; i++)
		{
			bp.mPassengers[bp.mCount++] = new Person(*(boat.mPassengers[i]));
			delete boat.mPassengers[i];
		}

		this->mCount = 0;
		plane.mCount = 0;

		return bp;
	}

	unsigned int Boat::GetMaxSpeed() const
	{
		return 0;
	}

	unsigned int Boat::GetSailSpeed() const
	{
		return 0;
	}

	void Boat::Travel()
	{
	}
}