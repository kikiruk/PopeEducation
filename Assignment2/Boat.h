#pragma once
#include "Vehicle.h"

#include "Boatplane.h"

namespace assignment2
{
	class Airplane;

	class Boat : Vehicle
	{
	public:
		Boat(unsigned int maxPassengersCount);
		~Boat();

		Boatplane operator+(Airplane& plane);

		virtual unsigned int GetMaxSpeed() const;
	};
}