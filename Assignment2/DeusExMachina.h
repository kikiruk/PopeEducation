#pragma once

#include "Vehicle.h"

namespace assignment2
{
	class DeusExMachina
	{
	private:
		static DeusExMachina* mInstence;
		DeusExMachina();

	public:
		~DeusExMachina();
		static DeusExMachina* GetInstance();
		void Travel() const;
		bool AddVehicle(Vehicle* vehicle);
		bool RemoveVehicle(unsigned int i);
		const Vehicle* GetFurthestTravelled() const;
		Vehicle* GetVehicle(unsigned int) const;

	private:
		enum { mMaxCount = 10 };
		Vehicle* mVehicles[mMaxCount];
		unsigned int mCount;
	};
}
