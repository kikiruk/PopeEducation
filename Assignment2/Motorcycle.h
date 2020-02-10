#pragma once
#include "Vehicle.h"
#include "IDrivable.h"

namespace assignment2
{
	class Motorcycle : public Vehicle, IDrivable
	{
	public:
		Motorcycle();
		~Motorcycle();


		// Vehicle��(��) ���� ��ӵ�
		virtual unsigned int GetMaxSpeed() const override;


		// IDrivable��(��) ���� ��ӵ�
		virtual unsigned int GetDriveSpeed() const override;


		// Vehicle��(��) ���� ��ӵ�
		virtual void Travel() override;

	};
}