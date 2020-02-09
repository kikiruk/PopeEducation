#pragma once

#include "Boatplane.h"
#include "Vehicle.h"
#include "IFlyable.h"
#include "IDrivable.h"

namespace assignment2
{
	class Boat;

	class Airplane : Vehicle, IFlyable, IDrivable
	{
	public:
		Airplane(unsigned int maxPassengersCount);
		~Airplane();

		Boatplane operator+(Boat& boat);

		virtual unsigned int GetMaxSpeed() const;

		// IFlyable을(를) 통해 상속됨
		virtual unsigned int GetFlySpeed() const override;

		// IDrivable을(를) 통해 상속됨
		virtual unsigned int GetDriveSpeed() const override;
	};
}