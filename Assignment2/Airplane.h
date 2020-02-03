#pragma once

#include "Boatplane.h"
#include "Vehicle.h"

namespace assignment2
{
	class Boat;

	class Airplane : Vehicle
	{
	public:
		Airplane(unsigned int maxPassengersCount);
		~Airplane();

		Boatplane operator+(Boat& boat);

		virtual unsigned int GetMaxSpeed();
	};
}