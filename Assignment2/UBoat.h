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

		// Vehicle��(��) ���� ��ӵ�
		virtual unsigned int GetMaxSpeed() const override;

		// ISailable��(��) ���� ��ӵ�
		virtual unsigned int GetSailSpeed() const override;

		// IDivable��(��) ���� ��ӵ�
		virtual unsigned int GetDiveSpeed() const override;
	};
}