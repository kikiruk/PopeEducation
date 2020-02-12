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

		Boatplane(unsigned int maxPassengersCount, unsigned int count, const Person** passengers);
		virtual ~Boatplane() = default;

		virtual unsigned int GetMaxSpeed() const;

		// IFlyable��(��) ���� ��ӵ�
		virtual unsigned int GetFlySpeed() const override;

		// ISailable��(��) ���� ��ӵ�
		virtual unsigned int GetSailSpeed() const override;

		// Vehicle��(��) ���� ��ӵ�
		virtual void Travel() override;
	};
}