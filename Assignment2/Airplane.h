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
		~Airplane();

		Boatplane operator+(Boat& boat);

		virtual unsigned int GetMaxSpeed() const;

		// IFlyable��(��) ���� ��ӵ�
		virtual unsigned int GetFlySpeed() const override;

		// IDrivable��(��) ���� ��ӵ�
		virtual unsigned int GetDriveSpeed() const override;
	};
}