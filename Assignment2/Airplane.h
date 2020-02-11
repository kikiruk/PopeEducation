#pragma once
#include "Boatplane.h"
#include "Vehicle.h"
#include "IFlyable.h"
#include "IDrivable.h"

namespace assignment2
{
	class Boat;

	class Airplane : public Vehicle, IFlyable, IDrivable
	{
		friend Boat;

	public:
		Airplane(unsigned int maxPassengersCount);
		virtual ~Airplane();

		Boatplane operator+(Boat& boat);

		virtual unsigned int GetMaxSpeed() const;

		// IFlyable을(를) 통해 상속됨
		virtual unsigned int GetFlySpeed() const override;

		// IDrivable을(를) 통해 상속됨
		virtual unsigned int GetDriveSpeed() const override;

		// Vehicle을(를) 통해 상속됨
		virtual void Travel() override;
	};
}