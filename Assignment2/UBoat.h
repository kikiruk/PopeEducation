#pragma once
#include "Vehicle.h"
#include "ISailable.h"
#include "IDivable.h"

namespace assignment2
{
	class UBoat : public Vehicle, ISailable, IDivable
	{
	public:
		UBoat();
		~UBoat();

		// Vehicle을(를) 통해 상속됨
		virtual unsigned int GetMaxSpeed() const override;

		// ISailable을(를) 통해 상속됨
		virtual unsigned int GetSailSpeed() const override;

		// IDivable을(를) 통해 상속됨
		virtual unsigned int GetDiveSpeed() const override;

		// Vehicle을(를) 통해 상속됨
		virtual void Travel() override;
	};
}