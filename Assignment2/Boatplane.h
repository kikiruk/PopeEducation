#pragma once
#include "Vehicle.h"

namespace assignment2
{
	class Boatplane : Vehicle
	{
	public:
		Boatplane(unsigned int maxPassengersCount);
		~Boatplane();

		virtual unsigned int GetMaxSpeed();
	};
}