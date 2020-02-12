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
		for (unsigned int i = 0; i < mCount; i++)
			mVehicles[i]->Travel();
	}

	bool DeusExMachina::AddVehicle(Vehicle* vehicle)
	{
		if (mCount == mMaxCount)
			return false;

		vehicle->mDistance = 0;
		mVehicles[mCount++] = vehicle;

		return true;
	}

	bool DeusExMachina::RemoveVehicle(unsigned int i)
	{
		if (mCount <= i)
			return false;

		delete mVehicles[i];

		if (mCount - 1 != i)
			memcpy(mVehicles + i, mVehicles + i + 1, sizeof(Vehicle*) * (mCount - i - 1));

		mCount--;

		return true;
	}

	const Vehicle* DeusExMachina::GetFurthestTravelled() const
	{
		if (mCount == 0)
			return nullptr;

		if (mVehicles[0]->mDistance == 0)
			return mVehicles[0];

		unsigned int maxDistance = 0;
		const Vehicle* furthestTravelledVehicle = nullptr;

		for (unsigned int i = 0; i < mCount; i++)
		{
			if (mVehicles[i]->mDistance > maxDistance)
			{
				maxDistance = mVehicles[i]->mDistance;
				furthestTravelledVehicle = mVehicles[i];
			}
		}

		return furthestTravelledVehicle;
	}
	
	Vehicle* DeusExMachina::GetVehicle(unsigned int i) const
	{
		if (i >= mMaxCount)
			return nullptr;

		return mVehicles[i];
	}
}