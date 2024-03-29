#pragma once
#include "Vehicle.h"
#include "IDrivable.h"

namespace assignment2
{
	class Motorcycle : public Vehicle, IDrivable
	{
	public:
		Motorcycle();
		virtual ~Motorcycle() = default;

		const Motorcycle& operator=(const Motorcycle& other);

		// Vehicle을(를) 통해 상속됨
		virtual unsigned int GetMaxSpeed() const override;


		// IDrivable을(를) 통해 상속됨
		virtual unsigned int GetDriveSpeed() const override;


		// Vehicle을(를) 통해 상속됨
		virtual void Travel() override;

	};
}