#include "Airplane.h"
#include "Boat.h"
#include "Boatplane.h"

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
		Boatplane bp(0);
		return bp;
	}

	unsigned int Airplane::GetMaxSpeed() const
	{
		return 0;
	}

	unsigned int Airplane::GetFlySpeed() const
	{
		return 0;
	}

	unsigned int Airplane::GetDriveSpeed() const
	{
		return 0;
	}
}