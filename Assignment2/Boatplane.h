#pragma once
#include "Vehicle.h"
#include "IFlyable.h"
#include "ISailable.h"

namespace assignment2
{
	class Airplane;
	class Boat;

	class Boatplane : public Vehicle, IFlyable, ISailable
	{
		friend Airplane;
		friend Boat;
	public:
		Boatplane(unsigned int maxPassengersCount);

		Boatplane(unsigned int maxPassengersCount, Airplane* airplane, Boat* boat);
		virtual ~Boatplane() = default;

		virtual unsigned int GetMaxSpeed() const;

		// IFlyable을(를) 통해 상속됨
		virtual unsigned int GetFlySpeed() const override;

		// ISailable을(를) 통해 상속됨
		virtual unsigned int GetSailSpeed() const override;

		// Vehicle을(를) 통해 상속됨
		virtual void Travel() override;
	};
}