#include "DeusExMachina.h"
#include <cstring>

namespace assignment2
{
	DeusExMachina::DeusExMachina() :
		mCount(0)
	{
	}

	DeusExMachina* DeusExMachina::GetInstance()
	{
		static DeusExMachina hInstence;
		return &hInstence;
	}

	void DeusExMachina::Travel() const
	{
	}

	bool DeusExMachina::AddVehicle(Vehicle* vehicle)
	{
		if (mCount == mMaxCount)
			return false;

		mVehicles[mCount++] = vehicle;

		return true;
	}

	bool DeusExMachina::RemoveVehicle(unsigned int i)
	{
		if (mCount <= i)
			return false;

		delete mVehicles[i];
		memcpy(mVehicles + i, mVehicles + i + 1, sizeof(Vehicle*) * (mCount - i - 1));
		mCount--;
	}

	const Vehicle* DeusExMachina::GetFurthestTravelled() const
	{
		if(mCount == 0)
			return NULL;

		for (int i = 0; i < mCount; i++)
			mVehicles[i]->Travel;
	}
} 