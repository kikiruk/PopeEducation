#pragma once
#include "Vehicle.h"

#include "Boatplane.h"
#include "ISailable.h"

namespace assignment2
{
	class Airplane;
	class Boatplane;

	class Boat : public Vehicle, ISailable
	{
		friend Airplane;
		friend Boatplane;

	public:
		Boat(unsigned int maxPassengersCount);
		virtual ~Boat() = default;

		Boatplane operator+(Airplane& plane);

		virtual unsigned int GetMaxSpeed() const;
		virtual unsigned int GetSailSpeed() const;

		// Vehicle��(��) ���� ��ӵ�
		virtual void Travel() override;
	};
}