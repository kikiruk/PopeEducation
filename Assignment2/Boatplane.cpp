#include "Boatplane.h"

namespace assignment2
{
	Boatplane::Boatplane(unsigned int maxPassengersCount)
		:Vehicle(maxPassengersCount)
	{
	}

	Boatplane::~Boatplane()
	{
	}

	unsigned int Boatplane::GetMaxSpeed() const
	{
		return 0;
	}
	unsigned int Boatplane::GetFlySpeed() const
	{
		return 0;
	}
	unsigned int Boatplane::GetSailSpeed() const
	{
		return 0;
	}
}